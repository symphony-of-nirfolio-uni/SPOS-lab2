#include "AtomicLockable.h"
#include "CounterClass.h"
#include <vector>
#include <fstream>
#include <memory.h>

void AtomicLockable::lock() 
{
	while (lock_flag.test_and_set());
}

void AtomicLockable::unlock()
{
	lock_flag.clear();
}

/*bool AtomicLockable::try_lock()
{
	return !lock_flag.test_and_set();
}*/

void atomic_lock_bm(int tests, int start_amount, unsigned long long* counter, int steps)
{

	AtomicLockable lock;

	std::vector<std::unique_ptr<CounterClass> > counters;

	std::ofstream fout{ "Atomic counter benchmark.txt" };

	for (int i = 0; i < tests; i++)
	{
		for (int j = 0; j < start_amount + i; j++)
		{
			counters.push_back(std::make_unique<CounterClass>(lock, counter, steps));
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

		fout << "Test " << i << std::endl;
		fout << "Counted: " << *counter << std::endl;
		fout << "Process amount: " << start_amount + i << std::endl;
		fout << "Quickest thread: " << min << " ms" << std::endl;
		fout << "Slowest thread: " << max << " ms" << std::endl;
		fout << "Delta: " << max - min << " ms" << std::endl;
		fout << "Delta%: " << ((max - min) * 100) / max << "%" << std::endl << std::endl;

		*counter = 0;
	}
}