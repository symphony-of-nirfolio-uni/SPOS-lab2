#pragma once
#include <chrono>
#include <thread>
#include "AtomicLockable.h"

class CounterClass
{
public:
	CounterClass(AtomicLockable* lock, unsigned long long* counter, int steps);

	void increment_counter(AtomicLockable* lock, unsigned long long* counter, int steps);

	void join();

	int exec_time();

private:
	std::chrono::time_point<std::chrono::system_clock> start;

	std::chrono::time_point<std::chrono::system_clock> end;

	std::thread exec_thread;
};