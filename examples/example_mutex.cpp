#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex;

void worker(void *a) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 1000000; ++i) {
        counter++;
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv) {
    pthread_mutex_init(&mutex, NULL);

    pthread_t t1;
    pthread_t t2;
    int thread_id_1 = 1;
    int thread_id_2 = 1;

    pthread_create(&t1, NULL, (void *(*)(void *)) &worker, (void *) &thread_id_1);
    pthread_create(&t2, NULL, (void *(*)(void *)) &worker, (void *) &thread_id_2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter value: %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}
