#pragma once
#include "../FixnumLock/Lockable.h"

#include <atomic>
#include <thread>
#include <iostream>

class ImprovedBakeryLock : public Lockable<100>{

private:
  std::atomic<std::size_t> next_ticket = 0;
  std::atomic<std::size_t> now_serving = 0;

public:
	void lock() override
	{
		std::size_t thread_ticket = next_ticket++;
		while (thread_ticket != now_serving) {
			std::this_thread::yield();
		}
	}
	void unlock() override
	{
    now_serving++;
	}
};

