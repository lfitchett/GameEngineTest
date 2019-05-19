#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"

class Circle : public Shape
{
public:
	double Radius;

	virtual Point GetCenter() = 0;

	virtual ~Circle() {};

protected:
	Circle() {};
};

class StaticCircle : Circle
{
private:
	Point Center;

public:
	StaticCircle(double x, double y, double radius)
	{
		Center.x = x;
		Center.y = y;
		Radius = radius;
	}

};

class ReferenceCircle : public Circle
{
private:
	Point& Center;

public:
	ReferenceCircle(Point& center, double radius) : Center(center)
	{
		Radius = radius;
	}

	Point GetCenter() override {
		return Center;
	}
};

class MovingCircle : public Circle
{
private:
	std::function<Point()> Center;

public:
	MovingCircle(std::function<Point()> center, double radius)
	{
		Center = center;
		Radius = radius;
	}

	Point GetCenter() override {
		return Center();
	}
};