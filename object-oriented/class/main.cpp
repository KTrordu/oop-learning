#include <iostream>

class Point
{
public:
	void move(int, int);
	void print() const;
	bool isAtOrigin() const;
	friend void display(const Point&);

private:
	int m_x{}, m_y{};
	mutable unsigned int m_printCount{}; // mutable members can be changed even for const objects
};

// if we write the method definition inside the class, they will be inline

void Point::move(int new_x, int new_y)
{
	m_x = new_x;
	m_y = new_y;
}

void Point::print() const
{
	std::cout << "X= " << m_x << " Y= " << m_y << std::endl;
	std::cout << "Print count = " << ++m_printCount << std::endl;
}

bool Point::isAtOrigin() const
{
	return (m_x == 0) && (m_y == 0);
}

void display(const Point& p)
{
	std::cout << p.m_x << " " << p.m_y << std::endl;
}

int main(int argc, char const *argv[])
{
	Point point1;
	point1.move(30, 40);
	point1.print();

	if (point1.isAtOrigin())
	{
		std::cout << "point1 is at the origin" << std::endl;
	}
	else
	{
		std::cout << "point1 is NOT at the origin" << std::endl;
	}

	display(point1);

	// we can create dynamic objects this way
	Point *ptr1;
	ptr1 = new Point;

	Point *ptr2 = new Point;

	Point *ptr3 {new Point};

	ptr1->move(40, 50);
	ptr1->print();

	ptr2->print();

	if (ptr3->isAtOrigin())
	{
		std::cout << "The object pointed to by ptr3 is at the origin." << std::endl;
	}
	else
	{
		std::cout << "The object pointed to by ptr3 is NOT at the origin." << std::endl;
	}

	delete ptr1;
	delete ptr2;
	delete ptr3;

	// we can create arrays of objects
	Point array[10];
	array[0].move(15, 40);
	array[0].print();

	// member variables of const objects can't be changed
	const Point fixedPoint;
	// fixedPoint.move(10, 15); this will cause an error
	fixedPoint.print();

	// only const methods can operate one const objects
	// const methods can only invoke const methods

	return 0;
}