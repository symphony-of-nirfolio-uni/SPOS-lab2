#pragma once


#include "FixnumLock.h"	

#include <array>
#include <thread>
#include <mutex>
#include <numeric>


template<size_t Max_threads_count>
class Lockble : public FixnumLock
{

public:
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
};