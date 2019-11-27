#pragma once
#include "../FixnumLock/Lockable.h"

class DekkerLock : public Lockable<2>
{
	size_t favoured_thread;
	bool want_to_enter[2] = {false, false};
public:
	void lock()
	{
		size_t id = this->getId();
		size_t next_id = 1-id;
			
		want_to_enter[id] = true;
		favoured_thread = id;
		while (favoured_thread == id && want_to_enter[next_id]) {};
		/*
		while (want_to_enter[next_id])
		{
			if (favoured_thread == next_id)
			{
				want_to_enter[id] = false;
				while (favoured_thread == next_id) {
				}
				want_to_enter[id] = true;
			}
		}*/
	}

	void unlock()
	{
		size_t id = this->getId();
		/*size_t next_id = 1-id;
		favoured_thread = next_id;*/
		want_to_enter[id] = false;
	}
};

