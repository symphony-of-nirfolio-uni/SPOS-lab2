#pragma once

class FixnumLock
{
	virtual void lock() = 0;
	virtual void lockInterruptibly() = 0;
	virtual void unlock() = 0;
	virtual bool tryLock() = 0;
	virtual bool tryLock(size_t timeout) = 0;

	virtual size_t getId() = 0;
	virtual void register_thread() = 0;
	virtual void unregister_thread() = 0;
};