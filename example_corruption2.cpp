#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long *counter = nullptr;

void inc(long *l)
{
    auto ll = *l;
    auto *c = reinterpret_cast<char *>(&ll);
    c[3] += (c[11] + 1) % 8;
    c[0] += (c[2] + 1) % 8;
    *l = ll;
}

void worker(void *a)
{
    int thread_id = *(int *)a;
    for (int i = 0; i < 100000; ++i)
    {
        inc(counter);
        // (*counter)++;
        // if(thread_id == 1)
        //     *counter = *counter + 202;
        // else
        //     *counter = *counter + 101;
    }
}

int main(int argc, char **argv)
{
    unsigned char counter_v[16] = {};
    counter = (long *)(((char *)&counter_v) + 2);

    pthread_t t1;
    pthread_t t2;
    int thread_id_1 = 1;
    int thread_id_2 = 2;

    pthread_create(&t1, NULL, (void *(*)(void *)) & worker, (void *)&thread_id_1);
    sleep(3);
    pthread_create(&t2, NULL, (void *(*)(void *)) & worker, (void *)&thread_id_2);

    // for (int i = 0; i < 10000000; ++i)
    // {
    //     if (*counter != 500000005 && *counter != 900000009)
    //         printf("Counter value: %d\n", *counter);
    // }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter value: %d\n", *counter);
    printf("Counter value: 0x%08x\n", *counter);

    return 0;
}
