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
	virtual void register_thread() = 0;
	virtual void register_thread(std::thread::id id) = 0;
	virtual void unregister_thread() = 0;
	virtual void unregister_thread(std::thread::id id) = 0;
};