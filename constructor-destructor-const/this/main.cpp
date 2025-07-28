#include <iostream>
#include <cmath>

class Point
{
public:
	void move(int, int);
	void print() const;
	bool isAtOrigin() const;
	double distanceFromOrigin() const;
	const Point* maxDistanceFromOrigin(const Point& in_point) const;

private:
	int m_x{}, m_y{};
};

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

double Point::distanceFromOrigin() const
{
	return std::sqrt((m_x * m_x) + (m_y * m_y));
}

// if we want to return a reference instead of ptr,just replace * with & and delete & before the in_point
const Point* Point::maxDistanceFromOrigin(const Point& in_point) const
{
	if (distanceFromOrigin() > in_point.distanceFromOrigin()) return this; // this is the current object
	else return &in_point;
}

int main(int argc, char const *argv[])
{
	Point point1;
	point1.move(8, 15);

	Point point2;
	point2.move(9, 12);

	const Point* pointPtr;
	pointPtr = point1.maxDistanceFromOrigin(point2);
	pointPtr->print();
	point1.maxDistanceFromOrigin(point2)->print(); // calls can be chained
	delete pointPtr;

	return 0;
}