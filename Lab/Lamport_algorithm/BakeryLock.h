#pragma once


#include "FixnumLock.h"


class BakeryLock : public FixnumLock
{
	void lock() override
	{

	}

	void lockInterruptibly() override
	{

	}

	void unlock() override
	{

	}

	bool tryLock() override
	{
		return false;
	}

	bool tryLock(size_t timeout) override
	{
		return false;
	}


	size_t getId() override
	{
		return 0;
	}

	void register_thread() override
	{

	}

	void unregister_thread() override
	{

	}
};