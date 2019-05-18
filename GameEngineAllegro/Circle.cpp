#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"

class Circle : public Shape
{
public:
	Point Center;
	double Radius;

	Circle(double x, double y, double radius)
	{
		Center.x = x;
		Center.y = y;
		Radius = radius;
	}

	~Circle() {};

protected:
	Circle() {};
};

class MovingCircle : public Circle
{
public:
	Point& Center;
	MovingCircle(Point& center, double radius) : Center(center)
	{
		Radius = radius;
	}
};