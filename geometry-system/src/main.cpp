#include <iostream>
#include <cstdio>

import geometry;

using std::cout;
using std::endl;

const int MAX_SHAPES{100};  // Global constant
unsigned int g_operationCount{0};  // Global variable

void testValueVsReference(Point p) {  // Call by value
    p.move(999, 999);
    printf("Inside function (value): ");
    p.print();
}

void testReference(Point& p) {  // Call by reference
    p.move(888, 888);
    printf("Inside function (reference): ");
    p.print();
}

int main() {
    printf("=== C++ OOP Test Program ===\n");
    printf("Max shapes allowed: %d\n", ::MAX_SHAPES);  // Global scope operator
    
    // Auto keyword usage
    auto point1 = Point(10, 20);
    auto point2 = Point(5, 5, 15, 25);  // member initializer list constructor
    
    printf("\n=== Constructor Testing ===\n");
    point1.print();
    point2.print();
    
    // Copy constructor
    printf("\n=== Copy Constructor ===\n");
    Point point3{point1};
    point3.print();
    
    // Static member usage
    printf("Total points created: %u\n", Point::getPointCount());
    
    // Dynamic allocation (3 ways)
    printf("\n=== Dynamic Memory Allocation ===\n");
    Point* ptr1 = new Point;
    Point* ptr2 = new Point(30, 40);
    Point* ptr3{new Point(point2)};
    
    ptr1->print();
    ptr2->print();
    ptr3->print();
    
    // Object arrays
    printf("\n=== Object Arrays ===\n");
    Point pointArray[3] = {Point{}, Point{1, 2}};  // third uses default constructor
    for(int i = 0; i < 3; i++) {
        printf("Array[%d]: ", i);
        pointArray[i].print();
    }
    
    // Method chaining (reference return)
    printf("\n=== Method Chaining ===\n");
    printf("Before chaining: ");
    point1.print();
    point1.move(100, 200).move(300, 400);  // Chain method calls
    printf("After chaining: ");
    point1.print();
    
    // Circle testing
    printf("\n=== Circle Testing ===\n");
    Circle c1;
    Circle c2(5.0);
    Circle c3(Point(10, 10), 7.5);
    
    c1.print(); printf("\n");
    c2.print(); printf("\n");
    c3.print(); printf("\n");
    
    // Operator overloading
    printf("\n=== Operator Overloading ===\n");
    if (c3 > c2) {
        printf("c3 is bigger than c2\n");
    }
    if (c1 == Circle()) {
        printf("c1 equals default circle\n");
    }
    
    // Friend function usage
    printf("\n=== Friend Functions ===\n");
    displayPoint(point1);
    displayCircle(c2);
    
    // Function overloading
    printf("\n=== Function Overloading ===\n");
    printf("max(10.5, 20.3) = %.2f\n", max(10.5, 20.3));
    printf("max(10.5, 20.3, 15.7) = %.2f\n", max(10.5, 20.3, 15.7));
    
    // Reference vs value testing
    printf("\n=== Reference vs Value ===\n");
    Point testPoint(50, 60);
    printf("Original: ");
    testPoint.print();
    
    testValueVsReference(testPoint);  // Pass by value
    printf("After value call: ");
    testPoint.print();  // Should be unchanged
    
    testReference(testPoint);  // Pass by reference
    printf("After reference call: ");
    testPoint.print();  // Should be changed
    
    // Mutable member testing
    printf("\n=== Mutable Member Testing ===\n");
    const Point constPoint(100, 100);
    printf("Const point access count: %u\n", constPoint.getAccessCount());
    constPoint.print();  // This should increment mutable counter
    printf("After print, access count: %u\n", constPoint.getAccessCount());
    
    // CustomString testing
    printf("\n=== CustomString Testing ===\n");
    CustomString str1("Hello World");
    str1.print();
    printf("Length: %zu\n", str1.length());
    
    CustomString str2{str1};  // Copy constructor
    str2.print();
    
    // Final statistics
    printf("\n=== Final Statistics ===\n");
    printf("Total points: %u\n", Point::getPointCount());
    printf("Total circles: %u\n", Circle::getCircleCount());
    
    // Cleanup
    delete ptr1;
    delete ptr2;
    delete ptr3;
    
    printf("\nAfter cleanup, total points: %u\n", Point::getPointCount());
    
    return 0;
}