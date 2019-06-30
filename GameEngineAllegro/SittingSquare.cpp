#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

class Rectangle
{
private:
	Point location;
	double sideLength;
	//BitmapBase bitmap;
	CollidingEntity collisionChecker;

public:
	Rectangle(EventLoop &loop, SharedData &data, Point location, double sideLength) :
		location(location),
		sideLength(sideLength),
		//bitmap(loop, data, "Resources/Images/square.jpg"),
		collisionChecker(loop, data, makeHitbox())
	{
		//bitmap.setSize(sideLength / 2 - 1, sideLength / 2 - 1);
		//bitmap.location = location;
	}

private:
	Hitbox* makeHitbox()
	{
		std::vector<Point> points = {
					{22,-12},
					{6,-24},
					{-12,-22},
					{-24,-6},
					{-22,12},
					{-6,24},
					{13,22},
					{24,6},
		};

		for (Point& point : points) {
			point = point * (sideLength / 50) + location;
		}

		return new SingleHitbox(new Polygon(points), false);
	}
};