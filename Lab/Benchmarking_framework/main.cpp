#include <iostream>
#include <thread>
#include "Lockables.h"

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

int main() 
{
	int tests = 5;
	int start_amount = 2;

	int steps = 1'000'000;

	singlethreaded_time(steps);

	//imp_bakery_lock_bm(tests, start_amount, steps);

	bakery_lock_bm(tests, start_amount, steps);

	dekker_lock_bm(1, 2, steps);

	atomic_lock_bm(tests, start_amount, steps);

	semaphore_lock_bm(tests, start_amount, steps);

	mutex_lock_bm(tests, start_amount, steps);
}