#include <iostream>
#include <thread>
#include "AtomicLockable.h"
#include "SemaphoreLockable.h"

int main() 
{
	int tests = 5;
	int start_amount = 2;

	unsigned long long* counter = new unsigned long long;
	*counter = 0;

	int steps = 1000000;

	//atomic_lock_bm(tests, start_amount, counter, steps);

	semaphore_lock_bm(tests, start_amount, counter, steps);
}