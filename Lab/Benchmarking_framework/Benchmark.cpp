#include "Benchmark.h"
#include <fstream>

void benchmark(AbstractLockable& lock, std::vector<std::unique_ptr<CounterClass> >& counters,
				int tests, int start_amount, unsigned long long& counter, int steps, std::string const& name)
{
	std::ofstream fout{ name + " counter benchmark.txt" };

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
			int time = counters[j]->exec_time();
			if (min > time)
				min = time;

			if (max < time)
				max = time;
		}

		counters.clear();

		fout << "Test " << i << std::endl;
		fout << "Counted: " << counter << std::endl;
		fout << "Process amount: " << start_amount + i << std::endl;
		fout << "Quickest thread: " << min << " ms" << std::endl;
		fout << "Slowest thread: " << max << " ms" << std::endl;
		fout << "Delta: " << max - min << " ms" << std::endl;
		fout << "Delta%: " << ((max - min) * 100) / max << "%" << std::endl << std::endl;

		counter = 0;
	}
}