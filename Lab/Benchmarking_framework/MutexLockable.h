#pragma once
#include <mutex>
#include "AbstractLockable.h"

class MutexLockable : public AbstractLockable
{
public:
	void lock();

	void unlock();
private:
	std::mutex mut;
};

void mutex_lock_bm(int tests, int start_amount, int steps);