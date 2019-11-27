#pragma optimize("", off)

#include <iostream>
#include "Algorithm.h"

using std::cout;

int main()
{
	int step = 1000000;
	int answer = create_race_condition(step);
	cout << "Race condition\n";
	cout << "Value that has to be: " << step * 2 << '\n';
	cout << "Real value: " << answer << '\n';

	answer = dekkers_algorithm(step);
	cout << "\nDekker's algorithm\n";
	cout << "Value that has to be: " << step * 2 << '\n';
	cout << "Real value: " << answer << '\n';

}