#include "MutexLockable.h"
#include "CounterClass.h"
#include <vector>
#include <memory.h>
#include "Benchmark.h"

void MutexLockable::lock()
{
	mut.lock();
}

void MutexLockable::unlock()
{
	mut.unlock();
}

void mutex_lock_bm(int tests, int start_amount, int steps)
{

	MutexLockable lock;

	std::vector<std::unique_ptr<CounterClass> > counters;

	benchmark(lock, counters, tests, start_amount, steps, "Mutex");
}