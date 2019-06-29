#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

class Rectangle
{
private:
	Point location;
	double sideLength;
	BitmapBase bitmap;
	CollidingEntity collisionChecker;

public:
	Rectangle(EventLoop &loop, SharedData &data, Point location, double sideLength) :
		location(location),
		sideLength(sideLength),
		bitmap(loop, data, "Resources/Images/square.jpg"),
		collisionChecker(loop, data, makeHitbox())
	{
		bitmap.setSize(sideLength / 2 - 1, sideLength / 2 - 1);
		bitmap.location = location;
	}

private:
	Hitbox* makeHitbox()
	{
		double points[4][2] = {
					{location.x, location.y},
					{location.x + sideLength / 2, location.y},
					{location.x + sideLength / 2, location.y + sideLength / 2},
					{location.x, location.y + sideLength / 2}
		};

		return new SingleHitbox(new SizedPolygon<4>(points), false);
	}
};