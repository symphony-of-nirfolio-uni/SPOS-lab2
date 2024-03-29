#pragma once


#include "../FixnumLock/Lockable.h"
#include <array>
#include <algorithm> 
#include <thread>
#include <chrono>
#include <mutex>
#include <numeric>
#include <assert.h>
#include <iostream>
#include <atomic>


namespace bakery_lock
{
	template<size_t Max_threads_count>
	class BakeryLock : public Lockable<Max_threads_count>
	{
	protected:
		void lock_by_id(size_t id) override
		{
			assert(id < Max_threads_count);

			is_enter_array[id] = true;
			
			size_t max_item = 0;
			for (size_t i = 0; i < Max_threads_count; ++i)
			{
				size_t item = number_array[i];
				max_item = std::max(max_item, item);
			}
			number_array[id] = max_item + 1;

			is_enter_array[id] = false;

			for (size_t i = 0; i < Max_threads_count; ++i)
			{
				while (is_enter_array[i])
				{

				}

				while ((number_array[i] != 0) 
					&& (number_array[id] > number_array[i] || (number_array[id] == number_array[i] && id > i)))
				{

				}
			}
		}

		void unlock_by_id(size_t id) override
		{
			assert(id < Max_threads_count);
			number_array[id] = 0;
		}
			
	private:
		std::array<std::atomic_bool, Max_threads_count> is_enter_array{ false };
		std::array<volatile size_t, Max_threads_count> number_array{ 0 };
	};
}