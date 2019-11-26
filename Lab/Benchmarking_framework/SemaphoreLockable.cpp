#include "SemaphoreLockable.h"
#include "CounterClass.h"
#include <vector>
#include <memory.h>
#include "Benchmark.h"

SemaphoreLockable::SemaphoreLockable(std::unique_ptr<Semaphore>&& sem)
{
	this->sem = std::move(sem);
}

void SemaphoreLockable::lock()
{
	while(!sem->decr());
}

void SemaphoreLockable::unlock()
{
	sem->incr();
}

/*bool AtomicLockable::try_lock()
{
	return sem->decr();
}*/

void semaphore_lock_bm(int tests, int start_amount, unsigned long long& counter, int steps)
{

	SemaphoreLockable lock(std::make_unique<Semaphore>(1));

	std::vector<std::unique_ptr<CounterClass> > counters;

	benchmark(lock, counters, tests, start_amount, counter, steps, "Semaphore");
}