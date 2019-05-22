#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"

constexpr int MOVE_SPEED = 5;
constexpr int RADIUS = 50;

class BouncingCircle : public TickingEntity, public EntityWithData
{
private:
	bool movingRight = true;
	bool movingDown = true;
	BitmapBase bitmap;
	CollidingEntity collisionChecker;

public:
	BouncingCircle(EventLoop &loop, SharedData &data)
		: TickingEntity(loop),
		EntityWithData(data),
		bitmap(loop, data, "Resources/Images/blueCircle.png"),
		collisionChecker(loop, data, makeHitbox(), [this](CollisionResult result) {onCollision(std::move(result)); })
	{
		bitmap.setSize(RADIUS * 2, RADIUS * 2);
		bitmap.setLocation(rand() % data.displaySize.width, rand() % data.displaySize.height);
	}

	~BouncingCircle()
	{

	}

protected:
	void Tick() override
	{
		if (movingRight) {
			bitmap.currLocation.x += MOVE_SPEED;
			if (bitmap.currLocation.x > sharedData.displaySize.width) {
				bitmap.currLocation.x = 2 * sharedData.displaySize.width - bitmap.currLocation.x;
				movingRight = false;
			}
		}
		else {
			bitmap.currLocation.x -= MOVE_SPEED;
			if (bitmap.currLocation.x < 0) {
				bitmap.currLocation.x = 0 - bitmap.currLocation.x;
				movingRight = true;
			}
		}

		if (movingDown) {
			bitmap.currLocation.y += MOVE_SPEED;
			if (bitmap.currLocation.y > sharedData.displaySize.height) {
				bitmap.currLocation.y = 2 * sharedData.displaySize.height - bitmap.currLocation.y;
				movingDown = false;
			}
		}
		else {
			bitmap.currLocation.y -= MOVE_SPEED;
			if (bitmap.currLocation.y < 0) {
				bitmap.currLocation.y = 0 - bitmap.currLocation.y;
				movingDown = true;
			}
		}
	}


private:
	Hitbox* makeHitbox()
	{
		return new SingleHitbox(new MovingCircle([this] {return Point{ bitmap.currLocation.x + RADIUS, bitmap.currLocation.y + RADIUS }; }, RADIUS));
	}

	void onCollision(CollisionResult collision)
	{
		movingDown = collision->OtherCenter->x < bitmap.currLocation.x;
		movingRight = collision->OtherCenter->y < bitmap.currLocation.y;
	}
};