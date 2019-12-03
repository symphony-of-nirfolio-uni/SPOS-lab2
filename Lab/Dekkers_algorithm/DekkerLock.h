#pragma once
#include "../FixnumLock/Lockable.h"
#include <atomic>

class DekkerLock : public Lockable<2>
{
	std::atomic_size_t favoured_thread;
	std::atomic_bool want_to_enter[2] = { false, false };
protected:
	void lock_by_id(size_t id)
	{
		size_t next_id = 1 - id;

		want_to_enter[id] = true;

		while (want_to_enter[next_id])
		{
			if (favoured_thread == next_id)
			{
				want_to_enter[id] = false;
				while (favoured_thread == next_id) {
				}
				want_to_enter[id] = true;
			}
		}
	}

	void unlock_by_id(size_t id)
	{
		size_t next_id = 1 - id;
		favoured_thread = next_id;
		want_to_enter[id] = false;
	}
};