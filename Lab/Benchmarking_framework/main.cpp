#include <iostream>
#include <thread>
#include "AtomicLockable.h"
#include "CounterClass.h"
#include <vector>

int main() 
{
	AtomicLockable* lock = new AtomicLockable();

	unsigned long long* counter = new unsigned long long;
	*counter = 0;

	int steps = 1000000;

	std::vector<CounterClass*> counters;

	int tests = 4;
	int start_amount = 2;

	for (int i = 0; i < tests; i++)
	{
		for (int j = 0; j < start_amount + i; j++)
		{
			counters.push_back(new CounterClass(lock, counter, steps));
		}

		for (int j = 0; j < counters.size(); j++)
		{
			counters[j]->join();
		}

		int min = 1000000;
		int max = 0;

		for (int j = 0; j < counters.size(); j++)
		{
			if (min > counters[j]->exec_time())
				min = counters[j]->exec_time();

			if (max < counters[j]->exec_time())
				max = counters[j]->exec_time();

		}

		counters.clear();

		std::cout << "Test " << i << std::endl;
		std::cout << "Counted: " << *counter << std::endl;
		std::cout << "Process amount: " << start_amount + i << std::endl;
		std::cout << "Quickest thread: " << min << " ms" << std::endl;
		std::cout << "Slowest thread: " << max << " ms" << std::endl;
		std::cout << "Delta: " << max - min << " ms" << std::endl << std::endl;

		*counter = 0;
	}
}