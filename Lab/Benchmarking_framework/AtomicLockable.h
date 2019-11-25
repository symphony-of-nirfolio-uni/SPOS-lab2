#pragma once
#include "AbstractLockable.h"
#include <atomic>

class AtomicLockable : AbstractLockable {
public:
	void lock();

	void unlock();

	bool try_lock();
private:
	std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
};