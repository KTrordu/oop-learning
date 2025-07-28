#include <iostream>

import funcs;

int main(int argc, char const *argv[])
{
	double r = 5.42;
	std::cout << "Area: " << CircleArea(r) << " Circumference: " << CircleCircumference(r) << std::endl;

	return 0;
}