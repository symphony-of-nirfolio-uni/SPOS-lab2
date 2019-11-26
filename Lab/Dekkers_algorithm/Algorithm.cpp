#include "Algorithm.h"


int create_race_condition(int step)
{
	int counter = 0;
	thread first_thread = thread(increment_counter, step, std::ref(counter));
	thread second_thread = thread(increment_counter, step, std::ref(counter));
	first_thread.join();
	second_thread.join();
	return counter;
}

void increment_counter(int step, int& counter)
{
	for (int i = 0; i < step; ++i)
	{
		++counter;
	}
}