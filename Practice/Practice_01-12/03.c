#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_start(void *arg) {
    size_t thread_id = *((size_t *) arg);
    printf("hello, world from %zu\n", thread_id);

    return NULL;
}

int main(int argc, char **argv) {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        fputs("Failed to get N\n", stderr);
        return -1;
    }

    pthread_t *threads =
        malloc(n * sizeof(*threads));
    size_t *thread_args =
        malloc(n * sizeof(*thread_args));

    for (size_t i = 0; i < n; ++i) {
        thread_args[i] = i;
        if (0 != pthread_create(
                &threads[i],
                NULL,
                thread_start,
                (void *) &thread_args[i]
            )) {
            fputs("Failed to create a thread.\n", stderr);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (0 != pthread_join(threads[i], NULL)) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    }

    free(thread_args);
    thread_args = NULL;
    free(threads);
    threads = NULL;

    return 0;
}

