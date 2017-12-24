#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_start(void *arg) {
    printf("hello, world from %d", (int) arg);

    return NULL;
}

int main(int argc, char **argv) {
    unsigned int n;
    if (scanf("%u", &n) != 1) {
        fputs("Failed to get N\n", stderr);
        return -1;
    }

    pthread_t *threads =
        malloc(n * sizeof(*threads));

    for (unsigned int i = 0; i < n; ++i) {
        if (pthread_create(
                &threads[i],
                NULL,
                thread_start,
                (void *) i
            ) != 0) {
            fputs("Failed to create a thread.\n", stderr);
        }
    }

    for (unsigned int i = 0; i < n; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            fputs("Failed to wait for the thread to finish.\n", stderr);
        }
    }

    free(threads);
    threads = NULL;

    return 0;
}

