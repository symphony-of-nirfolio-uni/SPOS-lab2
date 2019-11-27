#include <iostream>
#include "Algorithm.h"

using std::cout;

int main()
{
	int step = 1000;
	int answer = create_race_condition(step);

	cout << "Value that has to be: " << step * 2 << '\n';
	cout << "Real value: " << answer << '\n';
}