#include "Semaphore.h"

Semaphore::Semaphore(int max)
{
	this->curr = max;
}

void Semaphore::incr()
{
	curr++;
}

bool Semaphore::decr()
{
	mut.lock();
	if (curr > 0)
		curr--;
	else
	{
		mut.unlock();
		return false;
	}

	mut.unlock();
	return true;
}