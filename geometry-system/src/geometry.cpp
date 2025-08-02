#include <iostream>
#include <cmath>
#include <cstring>

module geometry;

double const PI{3.14};

#pragma region Point
class Point
{
public:
	Point();
    Point(int x, int y);
    Point(int x, int y, int MINX, int MINY);
    Point(const Point& original);

    Point& move(int x, int y);
    void print() const;
    bool isAtOrigin() const;
    double distanceFromOrigin() const;
    const Point* maxDistanceFromOrigin(const Point& other) const;
    int getX() const;
    int getY() const;

    friend void displayPoint(const Point& p);

    static unsigned int getPointCount();
    unsigned int getAccessCount() const;

    ~Point();

private:
    int m_x, m_y;
	const int m_MINX;
    const int m_MINY;

    static inline unsigned int s_pointCount{};
    mutable unsigned int m_accessCount {};
};

Point::Point() : m_MINX{0}, m_MINY{0}
{
    m_x = m_MINX;
    m_y = m_MINY;
    s_pointCount++;
}

Point::Point(int x, int y) : m_MINX{0}, m_MINY{0}
{
    x >= m_MINX ? m_x = x : m_x = m_MINX;
    y >= m_MINY ? m_y = y : m_y = m_MINY;
    s_pointCount++;
}

Point::Point(int x, int y, int MINX, int MINY) : m_MINX{MINX}, m_MINY{MINY}
{
    x >= m_MINX ? m_x = x : m_x = m_MINX;
    y >= m_MINY ? m_y = y : m_y = m_MINY;
    s_pointCount++;
}

Point::Point(const Point& original) : m_MINX{original.m_MINX}, m_MINY{original.m_MINY}
{
    m_x = original.m_x;
    m_y = original.m_y;
    s_pointCount++;
}

Point& Point::move(int x, int y)
{
    x >= m_MINX ? m_x = x : m_x = m_MINX;
    y >= m_MINY ? m_y = y : m_y = m_MINY;
    m_accessCount++;
    return *this;
}

void Point::print() const
{
    std::cout << "X = " << m_x << " Y = " << m_y << std::endl;
    m_accessCount++;
}

bool Point::isAtOrigin() const
{
    m_accessCount++;
    return (m_x == 0) && (m_y == 0);
}

double Point::distanceFromOrigin() const
{
    m_accessCount++;
    return sqrt(m_x * m_x + m_y * m_y);
}

const Point* Point::maxDistanceFromOrigin(const Point& other) const
{
    m_accessCount++;
    if (distanceFromOrigin() > other.distanceFromOrigin()) return this;
    else return &other;
}

int Point::getX() const
{
    return m_x;
}

int Point::getY() const
{
    return m_y;
}

void displayPoint(const Point& p)
{
    std::printf("Point: (%d,%d)\n", p.m_x, p.m_y);
}

unsigned int Point::getPointCount()
{
    return s_pointCount;
}

unsigned int Point::getAccessCount() const
{
    m_accessCount;
    return m_accessCount;
}

Point::~Point()
{
    s_pointCount--;
}

#pragma endregion Point

#pragma region Circle

class Circle
{
public:
    Circle();
    Circle(double radius);
    Circle(const Point& center, double radius);
    Circle(const Circle& original);

    bool operator==(const Circle& other);
    bool operator>(const Circle& other);

    double area() const;
    double perimeter() const;
    void print() const;

    friend void displayCircle(const Circle& c);

    static unsigned int getCircleCount();
    unsigned int getAccessCount() const;

    ~Circle();

private:
   Point m_center;
   double m_radius;

   double m_MIN_radius{1.0};

   static inline unsigned int s_circleCount{};
   mutable unsigned int m_accessCount{}; 
};

Circle::Circle() : m_center {Point(0,0)}
{
    m_radius = m_MIN_radius;
    s_circleCount++;
}

Circle::Circle(double radius) : m_center {Point(0,0)}
{
    radius > 0 ? m_radius = radius : m_radius = m_MIN_radius;
    s_circleCount++;
}

Circle::Circle(const Point& center, double radius) : m_center {center}
{
    radius > 0 ? m_radius = radius : m_radius = m_MIN_radius;
    s_circleCount++;
}

bool Circle::operator==(const Circle& other)
{
    m_accessCount++;
    return (m_center.getX() == other.m_center.getX() && m_center.getY() == other.m_center.getY()) && (m_radius == other.m_radius);
}

bool Circle::operator>(const Circle& other)
{
    m_accessCount++;
    return m_radius > other.m_radius;
}

double Circle::area() const
{
    m_accessCount++;
    return PI * m_radius * m_radius;
}

double Circle::perimeter() const
{
    m_accessCount++;
    return 2 * PI * m_radius;
}

void Circle::print() const
{
    m_accessCount++;
    std::printf("Center: (%d,%d), Radius: %f\n", m_center.getX(), m_center.getY(), m_radius);
}

void displayCircle(const Circle& c)
{
    std::printf("Circle: Center(%d,%d), Radius:%f\n", c.m_center.getX(), c.m_center.getY(), c.m_radius);
}

unsigned int Circle::getCircleCount()
{
    return s_circleCount;
}

unsigned int Circle::getAccessCount() const
{
    m_accessCount;
    return m_accessCount;
}

Circle::~Circle()
{
    s_circleCount--;
}

#pragma endregion Circle

#pragma region CustomString

class CustomString
{
public:
    CustomString(const char* str);
    CustomString(const CustomString& original);

    void print() const;
    size_t length() const;

    ~CustomString();
private:
    char* m_data;
    size_t m_size;
};

CustomString::CustomString(const char* str)
{
    m_size = std::strlen(str);
    m_data = new char[m_size + 1];

    if (m_data)
    {
        for (unsigned int index = 0; index < m_size + 1; index++)
        {
            m_data[index] = str[index];
        }
    }
}

void CustomString::print() const
{
    std::cout << m_data << std::endl;
}

size_t CustomString::length() const
{
    return m_size;
}

CustomString::~CustomString()
{
    delete[] m_data;
}


#pragma endregion CustomString

#pragma region Utils

inline double max(double a, double b)
{
    return (a > b) ? a : b;
}

inline double max(double a, double b, double c)
{
    return max(max(a, b), c);
}

#pragma endregion Utils