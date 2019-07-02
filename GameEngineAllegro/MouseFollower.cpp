#include "pch.h"

#include "BitmapBase.cpp"
#include "ReactiveCollidingEntity.cpp"
#include "UnitVector.cpp"
#include "TickingEntity.cpp"

constexpr double size = 25;

class MouseFollower : TickingEntity<Calculation>
{
private:
	Point& location;
	ReactiveCollidingEntity collisionChecker;
	Vector collisionCorrection;

public:
	MouseFollower(EventLoop &loop, SharedData &data) :
		TickingEntity(loop),
		location(data.mouseLocation),
		collisionChecker(loop, data, makeHitbox(), [this](CollisionInformation& result) {onCollision(result); })
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
		/*std::vector<Point> points {
					{size, -size},
					{size, size},
					{-size, size},
					{-size, -size }
		};*/

		std::vector<Point> points {
					{0, -size},
					{size, 0},
					{0, size},
					{-size, 0 }
		};

		return new SingleHitbox(new MovingPolygon(points, location), false);
	}

	void onCollision(CollisionInformation& collision)
	{
		//double moveAmount = collision.isOtherMoving ? collision.overlap / 2 : collision.overlap;
		//collisionCorrection = collision.Direction * moveAmount;
	}
};