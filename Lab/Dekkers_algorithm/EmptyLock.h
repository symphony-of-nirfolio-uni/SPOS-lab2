#pragma once
#include "../FixnumLock/Lockable.h"

class EmptyLock : public Lockable<2>
{
protected:
	void lock_by_id(size_t id)
	{
	
	}

	void unlock_by_id(size_t id)
	{
		
	}
};

