#include <iostream>

class Point
{
public:
	Point(); // with Point() = default; we can provide an empty default constructor
	Point(int, int); // we can provide default values
	Point(int, int, int, int);

	void move(int, int);
	void print() const;
	bool isAtOrigin() const;

	const int MIN_X {}; 
	const int MIN_Y {};

private:
	int m_x, m_y;
};

Point::Point()
{
	m_x = 0;
	m_y = 0;
}

Point::Point(int firstX, int firstY)
{
	if (firstX >= MIN_X) m_x = firstX;
	else m_x = MIN_X;

	if (firstY >= MIN_Y) m_y = firstY;
	else m_y = MIN_Y;
}

// member initializer list is the only way to change a constant member
Point::Point(int firstMINX, int firstMINY, int firstX, int firstY)
	: MIN_X {firstMINX}, MIN_Y {firstMINY}
{
	if (firstX >= MIN_X) m_x = firstX;
	else m_x = MIN_X;

	if (firstY >= MIN_Y) m_y = firstY;
	else m_y = MIN_Y;
}

void Point::move(int new_x, int new_y)
{
	m_x = new_x;
	m_y = new_y;
}

void Point::print() const
{
	std::cout << "X= " << m_x << " Y= " << m_y << std::endl;
}

bool Point::isAtOrigin() const
{
	return (m_x == 0) && (m_y == 0);
}

int main(int argc, char const *argv[])
{
	Point point1;
	point1.print();

	Point *pointPtr;
	pointPtr = new Point(15, 24);
	pointPtr->print();
	delete pointPtr;

	// we can define array of objects with constructors
	Point array[] = {Point{}, Point{15, 25}};
	array[0].print();
	array[1].print();

	Point array2[2] = {Point{10,10}}; // the last object will be created with the default constructor
	array2[1].print();

	Point *resPoint = new Point(20, 15, 30, 10);
	resPoint->print();
	delete resPoint;

	return 0;
}