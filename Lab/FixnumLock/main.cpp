#include "FixnumLock.h"
#include "Lockable.h"
#include <iostream>


int main() 
{
	std::cout << static_cast<size_t>(-1) << ' ' << std::numeric_limits<size_t>::max();
}