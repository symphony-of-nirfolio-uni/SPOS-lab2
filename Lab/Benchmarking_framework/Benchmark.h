#pragma once
#include "AbstractLockable.h"
#include <vector>
#include <memory.h>
#include "CounterClass.h"
#include <string>
void benchmark(AbstractLockable& lock, std::vector<std::unique_ptr<CounterClass> >& counters,
	int tests, int start_amount, unsigned long long& counter, int steps, std::string const& name);