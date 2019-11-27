#pragma once
#include "../Lamport_algorithm/BakeryLock.h"
#include "AbstractLockable.h"

class BakeryLockable : public AbstractLockable
{
public:
	void lock();

	void unlock();

	void registerThread();

	void unregisterThread();
private:
	bakery_lock::BakeryLock<30> b_lock;
};

void bakery_lock_bm(int tests, int start_amount, int steps);