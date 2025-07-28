#include <iostream>
#include <cmath>

class Point
{
public:
	Point();

	void move(int, int);
	void print() const;
	bool isAtOrigin() const;
	double distanceFromOrigin() const;
	const Point* maxDistanceFromOrigin(const Point& in_point) const;

	unsigned int getPointCount() const;

	// static methods can be called without objects
	// static methods can be invoked from outside the class
	// static methods can operate on static member variables regardless there are any objects
	// static methods can be used to initialize static data members before any objects created
	~Point();

private:
	int m_x{}, m_y{};
	static inline unsigned int s_point_count {}; // static members must be declared as inline
	// static members exist even if there are no objects
	// static members are created only once and shared amongst all the objects
};

Point::Point()
{
	s_point_count++;
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

double Point::distanceFromOrigin() const
{
	return std::sqrt((m_x * m_x) + (m_y * m_y));
}

const Point* Point::maxDistanceFromOrigin(const Point& in_point) const
{
	if (distanceFromOrigin() > in_point.distanceFromOrigin()) return this;
	else return &in_point;
}

unsigned int Point::getPointCount() const
{
	return s_point_count;
}

Point::~Point()
{
	s_point_count--;
}

int main(int argc, char const *argv[])
{
	Point point1, point2, point3;
	std::cout << point1.getPointCount() << std::endl;

	return 0;
}