#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr double size = 25;

class MouseFollower : TickingEntity
{
private:
	Point& location;
	CollidingEntity collisionChecker;
	Vector collisionCorrection;

public:
	MouseFollower(EventLoop &loop, SharedData &data) :
		TickingEntity(loop),
		location(data.mouseLocation),
		collisionChecker(loop, data, makeHitbox(), [this](CollisionInformation* result) {onCollision(result); }),
		collisionCorrection(0,0)
	{	}

protected:
	void Tick() override 
	{
		location.x += collisionCorrection.x;
		location.y += collisionCorrection.y;
		collisionCorrection.x = 0;
		collisionCorrection.y = 0;
	}

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
		collisionCorrection = collision->Direction * moveAmount;
	}
};