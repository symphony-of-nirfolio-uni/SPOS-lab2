#pragma once


#include "FixnumLock.h"	

#include <array>
#include <thread>
#include <mutex>
#include <numeric>
#include <assert.h>
#include <unordered_map>
#include <exception>


thread_local size_t thread_id{ std::numeric_limits<size_t>::max() };


template<size_t Max_threads_count>
class Lockable : public FixnumLock
{
private:
	std::array<size_t, Max_threads_count> thread_id_array{ std::numeric_limits<size_t>::max() };
	std::mutex thread_id_to_number_lock{};
	std::unordered_map < std::thread::id, size_t > thread_id_map;
	bool reset{ 0 };

public:


	void lock() override
	{
		lock(thread_id);
	}

	void unlock() override
	{
		lock(thread_id);
	}

	size_t getId() override
	{
		if (thread_id != -1)
		{
			return thread_id;
		}

		
		// thread not found
		assert(false);
		throw;
	}

	
	void registerThread() override
	{
		std::thread::id id = std::this_thread::get_id();
		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			if (thread_id_array[i] == std::numeric_limits<size_t>::max())
			{
				thread_id_array[i] = id;
				thread_id = id;
				return;
			}
		}

		// has no free space
		assert(false);
		throw;
	}

	void unregisterThread() override
	{
		std::thread::id id = std::this_thread::get_id();
		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			if (thread_id_array[i] == id)
			{
				thread_id_array[i] = std::numeric_limits<size_t>::max();
				thread_id = std::numeric_limits<size_t>::max();
				return;
			}
		}

		// thread not found
		assert(false);
		throw;
	}

	/*void reset() override
	{
		std::lock_guard<std::mutex> lock(thread_id_to_number_lock);

		for (size_t i = 0; i < thread_id_array.size(); ++i)
		{
			thread_id_array[i] = std::numeric_limits<size_t>::max();
		}
	}*/

};