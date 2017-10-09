#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct thread_arg {
    int *numbers;
    size_t length;
} thread_arg_t;

static int Sum = 0; // should be 605 at the end
static pthread_mutex_t Sum_Mutext = PTHREAD_MUTEX_INITIALIZER;

static void *thread_start(void *arg) {
    thread_arg_t *thread_args = (thread_arg_t *) arg;
    int *numbers = thread_args->numbers;
    size_t length = thread_args->length;
    for (size_t i = 0; i < length; ++i) {
        pthread_mutex_lock(&Sum_Mutext);
        Sum += numbers[i];
        pthread_mutex_unlock(&Sum_Mutext);
    }

    return NULL;
}

int main(int argc, char **argv) {
    int firstSequence[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
    int secondSequence[] = {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100
    };

    pthread_t threads[2];
    thread_arg_t thread_args[2];

    thread_args[0].numbers =
        firstSequence;
    thread_args[0].length =
        sizeof(firstSequence) /
            sizeof(firstSequence[0]);
    thread_args[1].numbers =
        secondSequence;
    thread_args[1].length =
        sizeof(secondSequence) /
            sizeof(secondSequence[0]);

    for (size_t i = 0; i < 2; ++i) {
        if (0 != pthread_create(
                &threads[i],
                NULL,
                thread_start,
                (void *) &thread_args[i]
            )) {
            fputs("Failed to create a thread.\n", stderr);
        }
    }

    for (size_t i = 0; i < 2; ++i) {
        if (0 != pthread_join(threads[i], NULL)) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    }

    printf("The total sum of two arrays is %d.\n", Sum);

    return 0;
}

