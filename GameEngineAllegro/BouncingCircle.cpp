#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"

constexpr int MOVE_SPEED = 10;
constexpr int RADIUS = 50;

class BouncingCircle : public TickingEntity, public EntityWithData
{
private:
	bool movingRight = true;
	bool movingDown = true;
	Point location;
	BitmapBase bitmap;
	CollidingEntity collisionChecker;

public:
	BouncingCircle(EventLoop &loop, SharedData &data)
		: TickingEntity(loop),
		EntityWithData(data),
		location{ (double)(rand() % data.displaySize.width), (double)(rand() % data.displaySize.height) },
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
		if (movingRight) {
			location.x += MOVE_SPEED;
			if (location.x > sharedData.displaySize.width) {
				location.x = 2 * sharedData.displaySize.width - location.x;
				movingRight = false;
			}
		}
		else {
			location.x -= MOVE_SPEED;
			if (location.x < 0) {
				location.x = 0 - location.x;
				movingRight = true;
			}
		}

		if (movingDown) {
			location.y += MOVE_SPEED;
			if (location.y > sharedData.displaySize.height) {
				location.y = 2 * sharedData.displaySize.height - location.y;
				movingDown = false;
			}
		}
		else {
			location.y -= MOVE_SPEED;
			if (location.y < 0) {
				location.y = 0 - location.y;
				movingDown = true;
			}
		}

		bitmap.setLocation(location);
	}


private:
	Hitbox* makeHitbox()
	{
		return new SingleHitbox(new MovingCircle([this] {return Point{ location.x + RADIUS, location.y + RADIUS }; }, RADIUS));
	}

	void onCollision(CollisionResult collision)
	{
		movingDown = collision->OtherCenter->x < location.x;
		movingRight = collision->OtherCenter->y < location.y;
	}
};