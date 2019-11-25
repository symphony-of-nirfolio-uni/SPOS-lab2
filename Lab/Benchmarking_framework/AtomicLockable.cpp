#include "AtomicLockable.h"

void AtomicLockable::lock() 
{
	while (lock_flag.test_and_set());
}

void AtomicLockable::unlock()
{
	lock_flag.clear();
}

bool AtomicLockable::try_lock()
{
	return !lock_flag.test_and_set();
}