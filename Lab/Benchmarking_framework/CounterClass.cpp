#include "CounterClass.h"
#include "BakeryLockable.h"

CounterClass::CounterClass(AbstractLockable& lock, int& counter, int steps)
{
	start = std::chrono::system_clock::now();

	exec_thread = std::thread(&CounterClass::increment_counter, this, std::ref(lock), std::ref(counter), steps);
}

void CounterClass::increment_counter(AbstractLockable& lock, int& counter, int steps)
{
	BakeryLockable* bakery = dynamic_cast<BakeryLockable*>(&lock);
	if (bakery)
	{
		bakery->registerThread();
	}

	for (int i = 0; i < steps; i++) 
	{
		lock.lock();
		counter += 1;
		lock.unlock();
	}

	if (bakery)
	{
		bakery->unregisterThread();
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