#include "DekkerLockable.h"
#include "CounterClass.h"
#include <vector>
#include <memory.h>
#include "Benchmark.h"

void DekkerLockable::lock()
{
	dek_lock.lock();
}

void DekkerLockable::unlock()
{
	dek_lock.unlock();
}

void DekkerLockable::registerThread()
{
	dek_lock.registerThread();
}

void DekkerLockable::unregisterThread()
{
	dek_lock.unregisterThread();
}

void dekker_lock_bm(int tests, int start_amount, int steps)
{

	DekkerLockable lock;

	std::vector<std::unique_ptr<CounterClass> > counters;

	benchmark(lock, counters, tests, start_amount, steps, "Dekker");
}