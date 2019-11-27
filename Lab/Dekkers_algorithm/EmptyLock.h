#pragma once
#include "../FixnumLock/Lockable.h"

class EmptyLock : public Lockable<2>
{
public:
	void lock()
	{
	
	}

	void unlock()
	{
		
	}
};

