#include "pch.h"

#include "BitmapBase.cpp"
#include "ReactiveCollidingEntity.cpp"
#include "UnitVector.cpp"
#include "TickingEntity.cpp"

constexpr int MOVE_SPEED = 0;
constexpr int RADIUS = 20;

class BouncingCircle : public TickingEntity<Calculation>
{
private:
	UnitVector direction;
	Point location;
	BitmapBase bitmap;
	ReactiveCollidingEntity collisionChecker;
	Vector collisionCorrection;

public:
	BouncingCircle(EventLoop &loop, SharedData &data) :
		TickingEntity(loop),
		direction((float)rand(), (float)rand()),
		location{ (double)((rand() % (data.displaySize.width / 2)) + data.displaySize.width / 4), (double)((rand() % (data.displaySize.height / 2)) + data.displaySize.height / 4) },
		bitmap(loop, data, "Resources/Images/blueCircle.png"),
		collisionChecker(loop, data, makeHitbox(), [this](CollisionInformation& result) {onCollision(result); })
	{
		bitmap.setSize(RADIUS * 2, RADIUS * 2);
	}

protected:
	void Tick() override
	{
		location.x += collisionCorrection.x;
		location.y += collisionCorrection.y;
		collisionCorrection.x = 0;
		collisionCorrection.y = 0;

		location.x += direction.x * MOVE_SPEED;
		location.y += direction.y * MOVE_SPEED;

		bitmap.location = location;
	}


private:
	Hitbox* makeHitbox()
	{
		return new SingleHitbox(new Circle(location, RADIUS), true);

		/*double points[4][2] = {
					{location.x, location.y},
					{location.x + RADIUS * 2, location.y},
					{location.x + RADIUS * 2, location.y + RADIUS * 2},
					{location.x, location.y + RADIUS * 2}
		};

		return new SingleHitbox(new MovingPolygon<4>([this] {return Point{ location.x + RADIUS, location.y + RADIUS }; }, points), true);*/
	}

	void onCollision(CollisionInformation& collision)
	{
		Vector pseudoWall = collision.Direction.ToNorm();
		direction = direction.Reflect(pseudoWall);

		double moveAmount = collision.isOtherMoving ? collision.overlap / 2 : collision.overlap;
		collisionCorrection = collision.Direction * moveAmount;
	}
};