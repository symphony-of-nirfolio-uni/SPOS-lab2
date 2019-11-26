#pragma once


#include "FixnumLock.h"
#include <array>
#include <algorithm> 
#include <thread>
#include <chrono>
#include <mutex>
#include <numeric>
#include <assert.h>


namespace bakery_lock
{
	template<size_t Max_threads_count>
	class BakeryLock : public FixnumLock
	{
	public:
		void lock() override
		{
			size_t id = getId();
			assert(id != std::numeric_limits<size_t>::max());

			is_enter_array[id] = true;

			size_t max_item = number_array[0];
			for (size_t i = 0; i < Max_threads_count; ++i)
			{
				max_item = std::max(max_item, number_array[i]);
			}
			number_array[id] = max_item + 1;

			is_enter_array[id] = false;

			for (size_t i = 0; i < Max_threads_count; ++i)
			{
				while (is_enter_array[i])
				{
					std::this_thread::yield();
				}

				while ((number_array[i] != 0) 
					&& (number_array[id] > number_array[i] || (number_array[id] == number_array[i] && id > i)))
				{
					std::this_thread::yield();
				}
			}
		}

		void unlock() override
		{
			size_t id = getId();
			assert(id != std::numeric_limits<size_t>::max());

			number_array[id] = 0;
		}

		bool tryLock() override
		{
			size_t id = getId();
			assert(id != std::numeric_limits<size_t>::max());

			// This algorithm does not support this method.
			assert(false);

			return false;
		}

		bool tryLock(size_t timeout_in_milliseconds) override
		{
			size_t id = getId();
			assert(id != std::numeric_limits<size_t>::max());

			// This algorithm does not support this method.
			assert(false);

			return false;
		}


		size_t getId() override
		{
			std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

			std::thread::id id = std::this_thread::get_id();
			for (size_t i = 0; i < thread_id_array.size(); ++i)
			{
				if (thread_id_array[i] == id)
				{
					return i;
				}
			}

			return std::numeric_limits<size_t>::max();
		}

		void registerThread() override
		{
			registerThread(std::this_thread::get_id());
		}

		void registerThread(std::thread::id id) override
		{
			std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

			for (size_t i = 0; i < thread_id_array.size(); ++i)
			{
				if (thread_id_array[i] == std::thread::id{})
				{
					thread_id_array[i] = id;
					return;
				}
			}
		}

		void unregisterThread() override
		{
			unregisterThread(std::this_thread::get_id());
		}


		void unregisterThread(std::thread::id id) override
		{
			std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

			for (size_t i = 0; i < thread_id_array.size(); ++i)
			{
				if (thread_id_array[i] == id)
				{
					thread_id_array[i] = std::thread::id{};
					return;
				}
			}
		}

	private:
		std::array<bool, Max_threads_count> is_enter_array{ false };
		std::array<size_t, Max_threads_count> number_array{ 0 };

		std::array<std::thread::id, Max_threads_count> thread_id_array{};
		std::mutex thread_id_to_number_lock{};
	};
}