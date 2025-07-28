#include <iostream>

using std::cout;
using std::endl;

const int LIMIT {5}; // global variable

int func(); // function signature

int main(int argc, char const *argv[])
{
	int counter {}; // initialized to zero
	cout << counter << endl;

	// auto automatically deduces the type
	auto v1 {10};
	auto v2 {35UL};
	auto v3 {3.56f};
	auto v4 {3.56d};

	cout << typeid(v1).name() << endl;
	cout << typeid(v2).name() << endl;
	cout << typeid(v3).name() << endl;
	cout << typeid(v4).name() << endl;

	// to deduce a reference type auto& or const auto& should be used

	cout << func() << endl;

	return 0;
}

int func()
{
	return LIMIT;
}