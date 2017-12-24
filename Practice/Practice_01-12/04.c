#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct thread_arg {
    unsigned int seconds;
} thread_arg_t;

void *thread_start(void *arg) {
    if (0 != pthread_detach(pthread_self())) {
        fputs("Failed to detach.\n", stderr);
        return NULL;
    }

    thread_arg_t *thread_args =
        (thread_arg_t *) arg;
    unsigned int seconds =
        thread_args->seconds;

    sleep(seconds);

    printf(
        "Alarm! %u seconds have passed\n",
        seconds
    );

    free(thread_args);
    thread_args = NULL;

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t thread_id;

    while (true) {
        unsigned int seconds;
        if (scanf("%u", &seconds) != 1) {
            fputs("Failed to get number of seconds\n", stderr);
            continue;
        }

        thread_arg_t *thread_arg =
            malloc(sizeof(*thread_arg));
        thread_arg->seconds = seconds;

        if (0 != pthread_create(
                &thread_id,
                NULL,
                thread_start,
                (void *) thread_arg
            )) {
            fputs("Failed to create a thread.\n", stderr);
        }
    } // loops forever

    return 0;
}

