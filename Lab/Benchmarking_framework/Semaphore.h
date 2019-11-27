#pragma once
#include <mutex>

class Semaphore 
{
public:
	Semaphore(int max);

	void incr();

	bool decr();
private:
	int curr;
	std::mutex mut;
};