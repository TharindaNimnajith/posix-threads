#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_barrier_t barrier;

void worker(void *a)
{
    sleep(2);
    pthread_barrier_wait(&barrier);
    sleep(10000); // Simulate long running actual work
}

int main(int argc, char **argv)
{
    pthread_barrier_init(&barrier, NULL, 3);

    pthread_t t1;
    pthread_t t2;
    int thread_id_1 = 1;
    int thread_id_2 = 1;

    pthread_create(&t1, NULL, (void *(*)(void *)) & worker, (void *)&thread_id_1);
    pthread_create(&t2, NULL, (void *(*)(void *)) & worker, (void *)&thread_id_2);

    pthread_barrier_wait(&barrier);
    printf("All threads are synced\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
