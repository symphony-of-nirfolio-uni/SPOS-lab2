#pragma once
#include "AbstractLockable.h"
#include "Semaphore.h"
#include <memory.h>

class SemaphoreLockable : public AbstractLockable {
public:
	SemaphoreLockable(std::unique_ptr<Semaphore>&& sem);

	void lock();

	void unlock();

	/*bool try_lock();*/
private:
	std::unique_ptr<Semaphore> sem;
};

void semaphore_lock_bm(int tests, int start_amount, unsigned long long& counter, int steps);