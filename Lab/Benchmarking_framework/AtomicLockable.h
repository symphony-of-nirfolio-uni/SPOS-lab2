#pragma once
#include "AbstractLockable.h"
#include <atomic>

class AtomicLockable : public AbstractLockable {
public:
	void lock();

	void unlock();
private:
	std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
};

void atomic_lock_bm(int tests, int start_amount, int steps);