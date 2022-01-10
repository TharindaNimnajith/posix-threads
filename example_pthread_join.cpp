#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void worker(void *a) {
    int *cnt = (int *) a;

    for (int i = 0; i < 10; ++i) {
        printf("This is thread %d\n", *cnt);
        sleep(1);
    }
}

int main(int argc, char **argv) {
    pthread_t t1;
    int thread_id = 1;

    if ((pthread_create(&t1, NULL, (void *(*)(void *)) &worker, (void *) &thread_id)) != 0) {
        printf("Error creating thread\n");
        exit(1);
    }

    printf("This is main thread, created a child thread\n");
    // sleep(20);
    pthread_join(t1, NULL);

    return 0;
}
