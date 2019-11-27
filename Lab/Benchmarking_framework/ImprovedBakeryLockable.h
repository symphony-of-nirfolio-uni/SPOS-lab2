#pragma once
#include "../ImprovedLamportAlgorithm/ImprovedBakeryLock.h"
#include "AbstractLockable.h"

class ImprovedBakeryLockable : public AbstractLockable
{
public:
	void lock();

	void unlock();
private:
	ImprovedBakeryLock imp_b_lock{};
};

void imp_bakery_lock_bm(int tests, int start_amount, int steps);
