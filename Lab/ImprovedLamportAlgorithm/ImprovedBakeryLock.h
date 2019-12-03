#pragma once
#include "../FixnumLock/Lockable.h"

#include <atomic>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

class ImprovedBakeryLock : public Lockable<100>{

private:
  std::atomic<std::size_t> next_ticket = 0;
  std::atomic<std::size_t> now_serving = 0;
  std::atomic<bool> locked = false;
  const std::size_t APPROX_BOUND_VALUE = 10'000'000;

protected:
	void lock_by_id(size_t id) override
	{
		if (next_ticket == APPROX_BOUND_VALUE - 1) locked = true;

		while (locked) {
			std::this_thread::yield();
		}

		size_t thread_ticket = next_ticket.fetch_add(1, std::memory_order_acquire);
		while (thread_ticket != now_serving) {
			std::this_thread::yield();
		}
	}
	void unlock_by_id(size_t id) override
	{
		now_serving++;
		if (now_serving == next_ticket) {
			restrictTickets();
			locked = false;
		}
	}

private:
	void restrictTickets()
	{
		next_ticket = 0;
		now_serving = 0;
	}
};

