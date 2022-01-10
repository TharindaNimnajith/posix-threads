#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <atomic>
#include "TimestampUtils.h"

std::atomic<int> counter{0};
// int counter = 0;
pthread_mutex_t mutex;

// thread_local int lcounter {0};
int64_t startTT = 0;

void worker(void *a)
{
	int lcounter = 0;
	for (int i = 0; i < 1000000; ++i)
	{
		// sleep(1);
		lcounter++;
	}
	// pthread_mutex_lock( &mutex );
	counter.fetch_add(lcounter, std::memory_order_relaxed);
	// counter += lcounter;
	// pthread_mutex_unlock( &mutex );
}

void workerNew(int a = -1)
{
	auto ts = getCurrentTimepoint();
	int lcounter = 0;
	for (int i = 0; i < 1000000; ++i)
	{
		// sleep(1);
		lcounter++;
	}
	// pthread_mutex_lock( &mutex );
	counter.fetch_add(lcounter, std::memory_order_relaxed);
	printf("threadStartDelay ns = %ld\n", ts - startTT);
}

struct A
{
	int x{0};
	void operator()()
	{
		auto ts = getCurrentTimepoint();
		printf("X = %d\n", x);
		printf("threadStartDelay ns = %ld\n", ts - startTT);
	}
};

int main(int argc, char **argv)
{
	pthread_mutex_init(&mutex, NULL);

	int thread_id_1 = 1;
	int thread_id_2 = 1;

	startTT = getCurrentTimepoint();

	// std::thread t1(worker, (void *)&thread_id_1);
	// std::thread t2(worker, (void *)&thread_id_2);

	std::thread t1(workerNew, thread_id_1);
	// std::thread t2(workerNew, thread_id_2);
	std::thread t2([&]() { workerNew(thread_id_2); });

	t1.join();
	t2.join();

	A a{7};
	std::thread tA(a);
	// std::thread tA([&](){a();});
	tA.join();

	printf("Counter value: %d\n", counter.load(std::memory_order_relaxed));
	// printf("Counter value: %d\n", counter);

	pthread_mutex_destroy(&mutex);

	return 0;
}
