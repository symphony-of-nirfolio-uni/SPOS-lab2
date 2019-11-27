#include "Algorithm.h"

int create_race_condition(int step)
{
	int counter = 0;
	thread first_thread = thread(increment_counter, step, ref(counter));
	thread second_thread = thread(increment_counter, step, ref(counter));
	first_thread.join();
	second_thread.join();
	return counter;
}

void increment_counter(int step, int &counter)
{
	for (int i = 0; i < step; ++i)
	{
		++counter;
	}
}

DekkerLock dekkerLock;

int dekkers_algorithm(int step)
{
	int counter = 0;

	thread first_thread = thread(dekkers_increment_counter, step, ref(counter));
	thread second_thread = thread(dekkers_increment_counter, step, ref(counter));

	first_thread.join();
	second_thread.join();
	return counter;
}


void dekkers_increment_counter(int step, int& counter)
{
	dekkerLock.registerThread();
	for (int i = 0; i < step; ++i)
	{
		dekkerLock.lock();
		++counter;
		dekkerLock.unlock();
	}
	dekkerLock.unregisterThread();
}

//part 3
bool check_on_raced(FixnumLock& lockable, int step)
{
	int counter = 0;

	thread first_thread = thread(race_increment_counter, ref(lockable), step, ref(counter));
	thread second_thread = thread(race_increment_counter, ref(lockable), step, ref(counter));

	first_thread.join();
	second_thread.join();

	if (counter != 2 * step)
		return true;
	else
		return false;
}

void race_increment_counter(FixnumLock& lockable, int step, int& counter)
{
	lockable.registerThread();
	for (int i = 0; i < step; ++i)
	{
		lockable.lock();
		++counter;
		lockable.unlock();
	}
	lockable.unregisterThread();
}

void test()
{
	int step = 1000000;
	//part 1
	int answer = create_race_condition(step);
	cout << "Race condition\n";
	cout << "Value that has to be: " << step * 2 << '\n';
	cout << "Real value: " << answer << '\n';

	//part 2
	answer = dekkers_algorithm(step);
	cout << "\nDekker's algorithm\n";
	cout << "Value that has to be: " << step * 2 << '\n';
	cout << "Real value: " << answer << '\n';

	//part 3
	cout << "\nCheck race condition\n";
	EmptyLock emptyLock;
	if (check_on_raced(emptyLock, step))
		cout << "EmptyLock has race condition.\n";
	else
		cout << "EmptyLock has no race condition.\n";

	if (check_on_raced(dekkerLock, step))
		cout << "Dekkers algorithm has race condition.\n";
	else
		cout << "Dekkers algorithm has no race condition.\n";
}
