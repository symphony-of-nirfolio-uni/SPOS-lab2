#include "Test.h"
#include "BakeryLock.h"

#include <iostream>


size_t const ThreadsCount = 4;
size_t const TestCount = 10000000;


bakery_lock::BakeryLock<ThreadsCount> bakeryLock;

long tested_value = 0;
std::array<size_t, ThreadsCount> currentNumbers{ 0 };


std::chrono::milliseconds timeout{ 10 };

void test_function(long number, size_t id)
{
	bakeryLock.registerThread();
	for (size_t i = 0; i < TestCount; ++i)
	{
		bakeryLock.lock();
	
		tested_value += number;

		currentNumbers[id] = i;

		bakeryLock.unlock();
	}
	bakeryLock.unregisterThread();
}


void inputTest()
{
	while (true)
	{
		long tested_value_to_output = tested_value;
		size_t currentNumbers_1 = currentNumbers[0];
		size_t currentNumbers_2 = currentNumbers[1];
		size_t currentNumbers_3 = currentNumbers[2];
		size_t currentNumbers_4 = currentNumbers[3];

		std::cout << tested_value_to_output << " counters: " << currentNumbers_1 << ' ' << currentNumbers_2 << ' ' << currentNumbers_3 << ' ' << currentNumbers_4 << '\n';

		if (currentNumbers[0] == TestCount - 1)
		{
			return;
		}

		std::this_thread::sleep_for(timeout);
	}
}

void test()
{
	std::array<long, ThreadsCount> parameters{-3, 0, 1, 2};

	std::cout << "Numbers: -3    0    1    2\n";

	std::random_shuffle(parameters.begin(), parameters.end());

	std::array<std::thread, ThreadsCount> threads{};

	for (size_t i = 0; i < ThreadsCount; ++i)
	{
		threads[i] = std::thread{ test_function, parameters[i], i };
	}

	std::thread input{ inputTest };

	for (size_t i = 0; i < ThreadsCount; ++i)
	{
		threads[i].join();
	}

	input.join();

	std::cout << "\nResult: " << tested_value << '\n';
}
