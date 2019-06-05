#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr double size = 25;

class MouseFollower
{
private:
	Point& location;
	CollidingEntity collisionChecker;

public:
	MouseFollower(EventLoop &loop, SharedData &data) :
		location(data.mouseLocation),
		collisionChecker(loop, data, makeHitbox(), [this](CollisionInformation* result) {onCollision(result); })
	{	}

private:
	Hitbox* makeHitbox()
	{
		double points[4][2] = {
					{-size, -size},
					{-size, size},
					{size, size},
					{size, -size }
		};


		Point test{ 10,0 };
		return new SingleHitbox(new MovingPolygon<2>([this] {return location; }, points, &test), true);
	}

	void onCollision(CollisionInformation* collision)
	{
		printf("mouse hit\n");
	}
};