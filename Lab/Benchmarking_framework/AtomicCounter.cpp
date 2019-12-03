#include "AtomicCounter.h"
#include "BakeryLockable.h"
#include <thread>

AtomicCounter::AtomicCounter(std::atomic_int& counter, int steps)
{
	start = std::chrono::system_clock::now();

	exec_thread = std::thread(&AtomicCounter::increment_counter, this, std::ref(counter), steps);
}

void AtomicCounter::increment_counter(std::atomic_int& counter, int steps)
{

	for (int i = 0; i < steps; i++)
	{
		counter += 1;
	}

	end = std::chrono::system_clock::now();
}

void AtomicCounter::join()
{
	exec_thread.join();
}

int AtomicCounter::exec_time()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}