#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// #include <iostream>
#include "TimestampUtils.h"

int64_t startTT = 0;

void *worker(void *a) {
    auto ts = getCurrentTimepoint();
    printf("threadStartDelay ns = %ld\n", ts - startTT);
    int *cnt = (int *) a;
    int counter = 0;
    for (int i = 0; i < 10; ++i) {
        printf("This is thread %d\n", *cnt);
        // std::cout << "This is thread " << *cnt << std::endl;
        sleep(1);
        ++counter;
        // if (i == 5)
        //     pthread_exit(nullptr);
    }
    return (void *) counter;
}

int main(int argc, char **argv) {
    pthread_t t1;
    int thread_id = 1;

    // using VoidFuncT = void* (*)(void*);

    startTT = getCurrentTimepoint();

    if ((pthread_create(&t1, NULL, &worker, (void *) &thread_id)) != 0) {
        printf("Error creating thread\n");
        exit(1);
    }

    printf("This is main thread, created a child thread\n");
    // std::cout << "This is main thread, created a child thread" << std::endl;

    int counterReturnValue = -1;

    sleep(2);
    // exit(0);
    pthread_exit(nullptr);

    pthread_join(t1, (void **) &counterReturnValue);

    printf("Output = %d\n", counterReturnValue);

    return 0;
}
