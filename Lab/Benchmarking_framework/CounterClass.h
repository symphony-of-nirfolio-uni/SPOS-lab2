#pragma once
#include <chrono>
#include <thread>
#include "AbstractLockable.h"

class CounterClass
{
public:
	CounterClass(AbstractLockable& lock, int& counter, int steps);

	void increment_counter(AbstractLockable& lock, int& counter, int steps);

	void join();

	int exec_time();

private:
	std::chrono::time_point<std::chrono::system_clock> start;

	std::chrono::time_point<std::chrono::system_clock> end;

	std::thread exec_thread;
};