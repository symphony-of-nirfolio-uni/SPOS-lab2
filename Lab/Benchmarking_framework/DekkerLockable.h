#pragma once
#include "../Dekkers_algorithm/DekkerLock.h"
#include "AbstractLockable.h"

class DekkerLockable : public AbstractLockable
{
public:
	void lock();

	void unlock();

	void registerThread();

	void unregisterThread();
private:
	DekkerLock dek_lock;
};

void dekker_lock_bm(int tests, int start_amount, int steps);