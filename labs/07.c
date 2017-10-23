#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_READERS 4
#define NUM_OF_WRITERS 1

static int Resource_Counter = 0;
static pthread_mutex_t Resource_Counter_Mutex =
    PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t Got_Resources_Condition =
    PTHREAD_COND_INITIALIZER;

static void *writer_start(void *arg) {
    static const size_t TIMES_TO_PRODUCE = 10;
    static const int ITEMS_TO_PRODUCE = 4;
    static const unsigned int PAUSE_IN_SEC = 5;

    for (size_t i = 0; i < TIMES_TO_PRODUCE; ++i) {
        pthread_mutex_lock(&Resource_Counter_Mutex);
        Resource_Counter += ITEMS_TO_PRODUCE;
        pthread_cond_broadcast(&Got_Resources_Condition);
        pthread_mutex_unlock(&Resource_Counter_Mutex);

        sleep(PAUSE_IN_SEC);
    }

    return NULL;
}

static void *reader_start(void *arg) {
    for (;;) {
        pthread_mutex_lock(&Resource_Counter_Mutex);
        while (Resource_Counter <= 0) {
            pthread_cond_wait(
                &Got_Resources_Condition,
                &Resource_Counter_Mutex
            );
        }
        printf("%d\n", Resource_Counter);
        pthread_mutex_unlock(&Resource_Counter_Mutex);

        // Do work on that data
    }

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t writer_threads[NUM_OF_WRITERS];
    pthread_t reader_threads[NUM_OF_READERS];

    for (size_t i = 0; i < NUM_OF_WRITERS; ++i) {
        if (0 != pthread_create(
                &writer_threads[i],
                NULL,
                writer_start,
                NULL
            )) {
            fputs("Failed to create a writer thread.\n", stderr);
        }
    }

    for (size_t i = 0; i < NUM_OF_READERS; ++i) {
        if (0 != pthread_create(
                &reader_threads[i],
                NULL,
                reader_start,
                NULL
            )) {
            fputs("Failed to create a readers thread.\n", stderr);
        }
    }

    for (size_t i = 0; i < NUM_OF_WRITERS; ++i) {
        if (0 != pthread_join(writer_threads[i], NULL)) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    }

    for (size_t i = 0; i < NUM_OF_READERS; ++i) {
        if (0 != pthread_join(reader_threads[i], NULL)) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    } // will wait forever

    return 0;
}

