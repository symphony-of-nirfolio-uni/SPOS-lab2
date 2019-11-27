#include "ImprovedBakeryLockable.h"
#include "CounterClass.h"
#include <vector>
#include <memory.h>
#include "Benchmark.h"

void ImprovedBakeryLockable::lock()
{
	imp_b_lock.lock();
}

void ImprovedBakeryLockable::unlock()
{
	imp_b_lock.unlock();
}

void imp_bakery_lock_bm(int tests, int start_amount, int steps)
{

	ImprovedBakeryLockable lock;

	std::vector<std::unique_ptr<CounterClass> > counters;

	benchmark(lock, counters, tests, start_amount, steps, "Improved bakery");
}