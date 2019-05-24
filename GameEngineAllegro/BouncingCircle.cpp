#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr int MOVE_SPEED = 10;
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
		collisionChecker(loop, data, makeHitbox(), [this](CollisionResult result) {onCollision(std::move(result)); })
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

		if (location.x < 0) {
			direction.x *= -1;
		}
		if (location.x + 2 * RADIUS > sharedData.displaySize.width) {
			direction.x *= -1;
		}

		if (location.y < 0) {
			direction.y *= -1;
		}
		if (location.y + 2 * RADIUS > sharedData.displaySize.height) {
			direction.y *= -1;
		}

		bitmap.setLocation(location);
	}


private:
	Hitbox* makeHitbox()
	{
		int points[4][2] = { {0,0},{RADIUS * 3,0},{RADIUS * 3,RADIUS * 3}, {0,RADIUS * 3} };
		return new SingleHitbox(
			new MovingPolygon<4>(
				[this] {return Point{ location.x + RADIUS, location.y + RADIUS }; },
				points
				)
		);
	}

	void onCollision(CollisionResult collision)
	{
		Vector pseudoWall = collision->Direction.ToNorm();
		direction = direction.Reflect(pseudoWall);

		double moveAmount = collision->isOtherMoving ? collision->overlap / 2 : collision->overlap;
		location.x += (moveAmount * collision->Direction.x);
		location.y += (moveAmount * collision->Direction.y);
	}
};