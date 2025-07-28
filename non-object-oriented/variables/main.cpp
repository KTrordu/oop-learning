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
	// to deduce a reference type auto& or const auto& should be used
	auto v1 {10};
	auto v2 {35UL};
	auto v3 {3.56f};
	auto v4 {3.56d};

	cout << typeid(v1).name() << endl;
	cout << typeid(v2).name() << endl;
	cout << typeid(v3).name() << endl;
	cout << typeid(v4).name() << endl;

	cout << func() << endl;

	int LIMIT = 6;
	cout << ::LIMIT << endl; // the :: operator makes us able to use the global variable


	/* const keyword with pointers */
	// const before * means data is constant
	const char *ptr {"ABC"};

	// const after * means the pointer is constant, meaning the address couldn't be changed
	int * const cp {&v1};
	*cp = 15; // OK, data is not constant

	// const before and after * means the data and pointer is constant
	const long unsigned int * const ccp {&v2};

	return 0;
}

int func()
{
	return LIMIT;
}