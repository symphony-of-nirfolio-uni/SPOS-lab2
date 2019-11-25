#include "CounterClass.h"

CounterClass::CounterClass(AtomicLockable* lock, unsigned long long* counter, int steps)
{
	start = std::chrono::system_clock::now();

	exec_thread = std::thread(&CounterClass::increment_counter, this, lock, counter, steps);
}

void CounterClass::increment_counter(AtomicLockable* lock, unsigned long long* counter, int steps)
{
	for (int i = 0; i < steps; i++) 
	{
		lock->lock();
		*counter += 1;
		lock->unlock();
	}

	end = std::chrono::system_clock::now();
}

void CounterClass::join()
{
	exec_thread.join();
}

int CounterClass::exec_time()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}