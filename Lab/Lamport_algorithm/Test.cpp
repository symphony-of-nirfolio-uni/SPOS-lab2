#include "Test.h"
#include "BakeryLock.h"

#include <iostream>


size_t const ThreadsCount = 4;
size_t const TestCount = 1'000'000;


bakery_lock::BakeryLock<ThreadsCount> bakeryLock;

long tested_value = 0;
size_t tested_index = 0;
std::array<long, ThreadsCount * TestCount> test_result;


void test_function(long number)
{
	for (size_t i = 0; i < TestCount; ++i)
	{
		bakeryLock.registerThread();

		bakeryLock.lock();
		tested_value += number;

		test_result[tested_index] = tested_value;
		++tested_index;

		bakeryLock.unlock();
		bakeryLock.unregisterThread();
	}
}


void test()
{
	std::array<long, ThreadsCount> parameters{};

	for (size_t i = 0; i < ThreadsCount / 2; ++i)
	{
		parameters[i] = -1;
	}
	for (size_t i = ThreadsCount / 2; i < ThreadsCount; ++i)
	{
		parameters[i] = 1;
	}

	std::random_shuffle(parameters.begin(), parameters.end());

	std::array<std::thread, ThreadsCount> threads{};

	for (size_t i = 0; i < ThreadsCount; ++i)
	{
		threads[i] = std::thread{ test_function, parameters[i] };
	}

	for (size_t i = 0; i < ThreadsCount; ++i)
	{
		threads[i].join();
	}

	for (size_t i = 0; i < ThreadsCount * TestCount; ++i)
	{
		std::cout << test_result[i] << ' ';
	}

	std::cout << "\nResult: " << tested_value << '\n';
}
