#include <iostream>
#include <cstring>

const int LIMIT {100};

inline int max(int num1, int num2) // inline functions are inserted as machine code at the call location
{
	return (num1 > num2) ? num1 : num2;
}

inline int max(int num1, int num2, int num3) // function overload
{
	std::cout << "This is overloaded." << std::endl;
	return -1;
}

void changeVal(bool flag)
{
	flag = !flag;
}

void changeRef(bool& flag)
{
	flag = !flag;
}

void func(char c, int num1 = 1, int num2 = max(4, 5)) // default values, also can be a function's return value
{
	std::cout << c << num1 << num2 << std::endl;
}

struct Person
{
	char name[40];
	unsigned int reg_num;
};

void print(const Person& per)
{
	std::cout << "Name: " << per.name << std::endl;
	std::cout << "Num: " << per.reg_num << std::endl;
}

int& returning()
{
	int i {};
	return i; // because i is local, it won't exist after the func call and should not be returned by reference.
}

int main(int argc, char const *argv[])
{
	for (int i = 0; i < LIMIT; i++)
	{
		//std::cout << max(i, i + 1) << std::endl;
	}

	func('A');
	func('B', 2);
	func('C', 3, 4);
	// func('D', , 5); this will cause an error, we can't skip a parameter

	max(1, 2, 3);

	// call by value can't change the value but call by reference can cuz it takes the address
	bool flag = false;
	std::cout << flag << std::endl;

	changeVal(flag);
	std::cout << flag << std::endl;

	changeRef(flag);
	std::cout << flag << std::endl;

	// We can send a reference as a parameter when we need to send big data. This way we can save up memory and don't lose much time.
	// Instead of 44 bytes, we sent 4 bytes.
	Person akyuz;
	strcpy(akyuz.name, "Ahmet Akyuez");
	akyuz.reg_num = 33;
	print(akyuz);

	return 0;
}