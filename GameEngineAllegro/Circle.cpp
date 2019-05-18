#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"

class Circle : public Shape
{
public:
	Point Center;
	double radius;

	~Circle() {};
};

class MovingCircle : public Circle
{
public:
	Point& Center;
	MovingCircle(Point& center) : Center(center) {}
};