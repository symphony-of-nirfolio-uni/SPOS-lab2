#include "BakeryLockable.h"
#include "CounterClass.h"
#include <vector>
#include <memory.h>
#include "Benchmark.h"

void BakeryLockable::lock()
{
	b_lock.lock();
}

void BakeryLockable::unlock()
{
	b_lock.unlock();
}

void BakeryLockable::registerThread()
{
	b_lock.registerThread();
}

void BakeryLockable::unregisterThread()
{
	b_lock.unregisterThread();
}

void bakery_lock_bm(int tests, int start_amount, int steps)
{

	BakeryLockable lock;

	std::vector<std::unique_ptr<CounterClass> > counters;

	benchmark(lock, counters, tests, start_amount, steps, "Bakery");
}