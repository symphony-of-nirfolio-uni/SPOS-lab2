#pragma once
#include <thread>
#include <iostream>

#include "DekkerLock.h"

using std::thread;
using std::ref;

int create_race_condition(int step);

void increment_counter(int step, int &counter);

int dekkers_algorithm(int step);

void dekkers_increment_counter(int step, int& counter);
