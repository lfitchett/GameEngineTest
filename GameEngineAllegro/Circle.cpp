#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"

class Circle : public Shape
{
public:
	double radius;
	Point& center;

	Circle(Point& center, double radius) : center(center), radius(radius) {}
};

class StaticCircle : Circle
{
private:
	Point centerStorage;

public:
	StaticCircle(double x, double y, double radius) : Circle(centerStorage, radius)
	{
		centerStorage.x = x;
		centerStorage.y = y;
	}

	StaticCircle(Point& center, double radius) : Circle(centerStorage, radius), centerStorage(center) {}
};