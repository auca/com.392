#include <stdio.h>
#include <pthread.h>

void *thread_start(void *arg) {
    puts("hello, world");

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t thread;
    pthread_create(
        &thread,
        NULL,
        thread_start,
        NULL
    );

    pthread_join(thread, NULL);

    return 0;
}

