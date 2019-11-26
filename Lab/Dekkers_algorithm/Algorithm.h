#pragma once
#include <thread>

using std::thread;

int create_race_condition(int step);

void increment_counter(int step, int &counter);

