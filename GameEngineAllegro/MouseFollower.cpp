#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr double size = 100;

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
					{location.x, location.y},
					{location.x + size / 2, location.y},
					{location.x + size / 2, location.y + size / 2},
					{location.x, location.y + size / 2}
		};

		return new SingleHitbox(new MovingPolygon<4>([this] {return location; }, points));
	}

	void onCollision(CollisionInformation* collision)
	{
		printf("mouse hit\n");
	}
};