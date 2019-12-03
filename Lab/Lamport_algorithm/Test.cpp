#include "Test.h"
#include "BakeryLock.h"

#include <iostream>


size_t const ThreadsCount = 5;
size_t const TestCount = 1000'000;


bakery_lock::BakeryLock<ThreadsCount> bakeryLock;

long tested_value = 0;
std::array<size_t, ThreadsCount> currentNumbers{};


std::chrono::milliseconds timeout{ 100 };

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
		std::cout << tested_value << " counters: ";
		for (size_t i = 0; i < ThreadsCount; ++i)
		{
			std::cout << currentNumbers[i] << ' ';
		}
		std::cout << '\n';
		
		if (currentNumbers[0] == TestCount - 1)
		{
			return;
		}

		std::this_thread::sleep_for(timeout);
	}
}

void test()
{
	std::array<long, ThreadsCount> parameters{ -6, 0, 1, 2, 3, };

	std::cout << "Numbers: -6    0    1    2    3\n";

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
