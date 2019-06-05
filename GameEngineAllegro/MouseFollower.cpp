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


		return new SingleHitbox(new MovingPolygon<4>([this] {return location; }, points), false);
	}

	void onCollision(CollisionInformation* collision)
	{
		double moveAmount = collision->isOtherMoving ? collision->overlap / 2 : collision->overlap;
		location.x += (moveAmount * collision->Direction.x);
		location.y += (moveAmount * collision->Direction.y);
	}
};