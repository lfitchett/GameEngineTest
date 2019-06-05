#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr int MOVE_SPEED = 3;
constexpr int RADIUS = 25;

class BouncingCircle : public TickingEntity, public EntityWithData
{
private:
	UnitVector direction;
	Point location;
	BitmapBase bitmap;
	CollidingEntity collisionChecker;

public:
	BouncingCircle(EventLoop &loop, SharedData &data)
		: TickingEntity(loop),
		EntityWithData(data),
		direction((float)rand(), (float)rand()),
		location{ (double)((rand() % (data.displaySize.width / 2)) + data.displaySize.width / 4), (double)((rand() % (data.displaySize.height / 2)) + data.displaySize.height / 4) },
		bitmap(loop, data, "Resources/Images/blueCircle.png"),
		collisionChecker(loop, data, makeHitbox(), [this](CollisionInformation* result) {onCollision(result); })
	{
		bitmap.setSize(RADIUS * 2, RADIUS * 2);
	}

	~BouncingCircle()
	{

	}

protected:
	void Tick() override
	{
		location.x += direction.x * MOVE_SPEED;
		location.y += direction.y * MOVE_SPEED;

		bitmap.setLocation(location);
	}


private:
	Hitbox* makeHitbox()
	{
		//return new SingleHitbox(new MovingCircle([this] {return Point{ location.x + RADIUS, location.y + RADIUS }; }, RADIUS), true);

		double points[4][2] = {
					{location.x, location.y},
					{location.x + RADIUS * 2, location.y},
					{location.x + RADIUS * 2, location.y + RADIUS * 2},
					{location.x, location.y + RADIUS * 2}
		};

		return new SingleHitbox(new MovingPolygon<4>([this] {return Point{ location.x + RADIUS, location.y + RADIUS }; }, points), true);
	}

	void onCollision(CollisionInformation* collision)
	{
		Vector pseudoWall = collision->Direction.ToNorm();
		direction = direction.Reflect(pseudoWall);

		double moveAmount = collision->isOtherMoving ? collision->overlap / 2 : collision->overlap;
		location.x += (moveAmount * collision->Direction.x);
		location.y += (moveAmount * collision->Direction.y);
		bitmap.setLocation(location);
	}
};