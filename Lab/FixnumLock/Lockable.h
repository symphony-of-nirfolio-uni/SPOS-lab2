#pragma once


#include "FixnumLock.h"	

#include <array>
#include <thread>
#include <mutex>
#include <numeric>
#include <assert.h>
#include <unordered_map>


template<size_t Max_threads_count>
class Lockable : public FixnumLock
{

public:


	void lock() override
	{
		lock(thread_id);
	}

	size_t getId() override
	{
		if (thread_id != -1)
		{
			return thread_id;
		}

		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		std::thread::id id = std::this_thread::get_id();
		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			if (thread_id_array[i] == id)
			{
				return i;
			}
		}

		// thread not found
		assert(false);
		
	}

	
	void registerThread() override
	{
		std::thread::id id = std::this_thread::get_id();
		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			if (thread_id_array[i] == std::thread::id{})
			{
				thread_id_array[i] = id;
				thread_id = id;
				return;
			}
		}

		// has no free space
		assert(false);
	}

	void unregisterThread() override
	{
		std::thread::id id = std::this_thread::get_id();
		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			if (thread_id_array[i] == id)
			{
				thread_id_array[i] = std::thread::id{};
				thread_id = -1;
				return;
			}
		}

		// thread not found
		assert(false);
	}

	void reset() override
	{
		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			thread_id_array[i] = std::thread::id{};
		}
	}

private:
	std::array<std::thread::id, Max_threads_count> thread_id_array{};
	std::mutex thread_id_to_number_lock{};
	std::unordered_map < std::thread::id, size_t > thread_id_map;
	thread_local size_t thread_id = -1;
};