#pragma once
#include<thread>

class FixnumLock
{
public:
	FixnumLock() {}

	FixnumLock(FixnumLock&&) = delete;
	FixnumLock& operator=(FixnumLock&&) = delete;

	virtual void lock() = 0;
	virtual void lock_by_id(size_t id) = 0;
	virtual void unlock() = 0;
	virtual void unlock_by_id(size_t id) = 0;

	virtual size_t getId() = 0;
	virtual void registerThread() = 0;
	virtual void unregisterThread() = 0;
};