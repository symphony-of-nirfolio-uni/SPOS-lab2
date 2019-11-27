#pragma once
#include <thread>
#include <iostream>

#include "DekkerLock.h"
#include "EmptyLock.h"

using std::thread;
using std::cout;
using std::ref;

//part 1
int create_race_condition(int step);
void increment_counter(int step, int &counter);

//part 2
int dekkers_algorithm(int step);
void dekkers_increment_counter(int step, int& counter);

//part 3
bool check_on_raced(FixnumLock& lockable, int step);
void race_increment_counter(FixnumLock& lockable, int step, int& counter);

//tes_all
void test();