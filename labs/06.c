#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_CONSUMERS 4
#define NUM_OF_PRODUCERS 1

static int Resource_Counter = 0;
static pthread_mutex_t Resource_Counter_Mutex =
    PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t Got_Resources_Condition =
    PTHREAD_COND_INITIALIZER;

static void *producer_start(void *arg) {
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

static void *consumer_start(void *arg) {
    for (;;) {
        pthread_mutex_lock(&Resource_Counter_Mutex);
        while (Resource_Counter <= 0) {
            pthread_cond_wait(
                &Got_Resources_Condition,
                &Resource_Counter_Mutex
            );
        }
        --Resource_Counter;
        pthread_mutex_unlock(&Resource_Counter_Mutex);

        // Do work on that data
    }

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t producer_threads[NUM_OF_PRODUCERS];
    pthread_t consumer_threads[NUM_OF_CONSUMERS];

    for (size_t i = 0; i < NUM_OF_PRODUCERS; ++i) {
        if (0 != pthread_create(
                &producer_threads[i],
                NULL,
                producer_start,
                NULL
            )) {
            fputs("Failed to create a producer thread.\n", stderr);
        }
    }

    for (size_t i = 0; i < NUM_OF_CONSUMERS; ++i) {
        if (0 != pthread_create(
                &consumer_threads[i],
                NULL,
                consumer_start,
                NULL
            )) {
            fputs("Failed to create a consumer thread.\n", stderr);
        }
    }

    for (size_t i = 0; i < NUM_OF_PRODUCERS; ++i) {
        if (0 != pthread_join(producer_threads[i], NULL)) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    }

    for (size_t i = 0; i < NUM_OF_CONSUMERS; ++i) {
        if (0 != pthread_join(consumer_threads[i], NULL)) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    } // will wait forever

    return 0;
}

