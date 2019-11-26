#include "AtomicLockable.h"
#include "CounterClass.h"
#include <vector>
#include <memory.h>
#include "Benchmark.h"

void AtomicLockable::lock() 
{
	while (lock_flag.test_and_set());
}

void AtomicLockable::unlock()
{
	lock_flag.clear();
}

void atomic_lock_bm(int tests, int start_amount, int steps)
{

	AtomicLockable lock;

	std::vector<std::unique_ptr<CounterClass> > counters;

	benchmark(lock, counters, tests, start_amount, steps, "Atomic");
}