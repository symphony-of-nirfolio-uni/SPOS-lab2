#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "Lockables.h"
#include "AtomicCounter.h"
#include <memory.h>

void singlethreaded_time(int steps)
{
	auto start = std::chrono::system_clock::now();

	int counter = 0;

	for (int i = 0; i < steps; i++)
		counter++;

	auto end = std::chrono::system_clock::now();

	int time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "Singlethreaded time for " << steps << " steps: " << time << " ms" << std::endl;
}

void atomic_inc(int steps, std::atomic_int counter)
{
	for (int i = 0; i < steps; i++)
		counter += 1;
}

void atomic_int_time(int tests, int start_amount, int steps)
{
	std::vector<std::unique_ptr<AtomicCounter> > counters;

	std::atomic_int counter = 0;

	for (int i = 0; i < tests; i++)
	{
		for (int j = 0; j < start_amount + i; j++)
		{
			counters.push_back(std::make_unique<AtomicCounter>(counter, steps));
		}

		for (int j = 0; j < counters.size(); j++)
		{
			counters[j]->join();
		}

		int min = 1000000;
		int max = 0;

		for (int j = 0; j < counters.size(); j++)
		{
			int time = counters[j]->exec_time();
			if (min > time)
				min = time;

			if (max < time)
				max = time;
		}

		counters.clear();

		std::cout << "Test " << i << std::endl;
		std::cout << "Counted: " << counter << std::endl;
		std::cout << "Process amount: " << start_amount + i << std::endl;
		std::cout << "Quickest thread: " << min << " ms" << std::endl;
		std::cout << "Slowest thread: " << max << " ms" << std::endl;
		std::cout << "Delta: " << max - min << " ms" << std::endl;
		std::cout << "Delta%: " << (((double)max - min) * 100) / max << "%" << std::endl << std::endl;

		counter = 0;
	}
}

int main() 
{
	int tests = 5;
	int start_amount = 2;

	int steps = 1'000'000;

	singlethreaded_time(steps);

	atomic_int_time(tests, start_amount, steps);

	dekker_lock_bm(1, 2, steps);

	atomic_lock_bm(tests, start_amount, steps);

	semaphore_lock_bm(tests, start_amount, steps);

	mutex_lock_bm(tests, start_amount, steps);

	imp_bakery_lock_bm(tests, start_amount, steps);

	bakery_lock_bm(tests, start_amount, steps);
}