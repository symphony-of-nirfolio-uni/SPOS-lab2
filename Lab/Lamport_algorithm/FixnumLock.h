#pragma once


#include <thread>


class FixnumLock
{
public:
	FixnumLock() {}

	FixnumLock(FixnumLock&&) = delete;
	FixnumLock& operator=(FixnumLock&&) = delete;

	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool tryLock() = 0;
	virtual bool tryLock(size_t timeout_in_milliseconds) = 0;

	virtual size_t getId() = 0;
	virtual void registerThread() = 0;
	virtual void registerThread(std::thread::id id) = 0;
	virtual void unregisterThread() = 0;
	virtual void unregisterThread(std::thread::id id) = 0;
};