#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"
#include "RectangleBound.cpp"

class Circle : public Shape
{
protected:
	RectangleBound bounds;

public:
	double radius;
	Point& center;

	virtual RectangleBound& GetBounds() { return bounds; };

	Circle(Point& center, double radius) : center(center), radius(radius)
	{
		setBounds();
	}

protected:
	void setBounds()
	{
		bounds.xMax = center.x + radius;
		bounds.yMax = center.y + radius;
		bounds.xMin = center.x - radius;
		bounds.yMin = center.y - radius;
	}
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

	RectangleBound& GetBounds() override
	{
		setBounds();
		return bounds;
	};
};