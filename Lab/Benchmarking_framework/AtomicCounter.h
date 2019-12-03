#pragma once
#include <chrono>
#include <thread>
#include <atomic>
#include "AbstractLockable.h"

class AtomicCounter
{
public:

	AtomicCounter(std::atomic_int& counter, int steps);

	void increment_counter(std::atomic_int& counter, int steps);

	void join();

	int exec_time();

private:
	std::chrono::time_point<std::chrono::system_clock> start;

	std::chrono::time_point<std::chrono::system_clock> end;

	std::thread exec_thread;
};