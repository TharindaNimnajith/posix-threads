#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

bool dataAvailable = false;
pthread_mutex_t mutex;

void producer(void *a)
{
    pthread_mutex_lock(&mutex);
    // Assume actual work is produce here
    dataAvailable = true;
    printf("Work is produced in the producer thread\n");
    pthread_mutex_unlock(&mutex);
}

void consumer(void *a)
{
    printf("Waiting from work in the consumer thread\n");
    while (!dataAvailable);
    printf("Found work in the consumer thread\n");
    pthread_mutex_lock(&mutex);
    // Assume actual work is processed here
    dataAvailable = false;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
    pthread_mutex_init(&mutex, NULL);

    pthread_t t1;
    pthread_t t2;
    int thread_id_1 = 1;
    int thread_id_2 = 1;

    pthread_create(&t1, NULL, (void *(*)(void *)) & consumer, (void *)&thread_id_1);
    sleep(5);
    pthread_create(&t2, NULL, (void *(*)(void *)) & producer, (void *)&thread_id_2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
