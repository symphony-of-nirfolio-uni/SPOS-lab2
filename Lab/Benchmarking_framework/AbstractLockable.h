#pragma once

class AbstractLockable {
public:
	virtual void lock() = 0;

	virtual void unlock() = 0;

	virtual bool try_lock() = 0;
};