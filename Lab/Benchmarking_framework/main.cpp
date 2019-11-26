#include <iostream>
#include <thread>
#include "AtomicLockable.h"
#include "SemaphoreLockable.h"
#include "BakeryLockable.h"

int main() 
{
	int tests = 5;
	int start_amount = 2;

	int steps = 1000000;

	atomic_lock_bm(tests, start_amount, steps);

	semaphore_lock_bm(tests, start_amount, steps);

	//bakery_lock_bm(tests, start_amount, counter, steps);
}