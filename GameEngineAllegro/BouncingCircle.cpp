#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"

constexpr int MOVE_SPEED = 10;
constexpr int RADIUS = 50;

class BouncingCircle : public BitmapBase, public TickingEntity, public CollidingEntity
{
private:
	bool movingRight = true;
	bool movingDown = true;

public:
	BouncingCircle(EventLoop &loop, SharedData &data)
		: BitmapBase(loop, data, "Resources/Images/blueCircle.png"),
		TickingEntity(loop),
		CollidingEntity(loop, data, makeHitbox())
	{
		setSize(RADIUS * 2, RADIUS * 2);
		setLocation(rand() % data.displaySize.width, rand() % data.displaySize.height);
	}

	~BouncingCircle()
	{

	}

protected:
	void Tick() override
	{
		if (movingRight) {
			currLocation.x += MOVE_SPEED;
			if (currLocation.x > BitmapBase::sharedData.displaySize.width) {
				currLocation.x = 2 * BitmapBase::sharedData.displaySize.width - currLocation.x;
				movingRight = false;
			}
		}
		else {
			currLocation.x -= MOVE_SPEED;
			if (currLocation.x < 0) {
				currLocation.x = 0 - currLocation.x;
				movingRight = true;
			}
		}

		if (movingDown) {
			currLocation.y += MOVE_SPEED;
			if (currLocation.y > BitmapBase::sharedData.displaySize.height) {
				currLocation.y = 2 * BitmapBase::sharedData.displaySize.height - currLocation.y;
				movingDown = false;
			}
		}
		else {
			currLocation.y -= MOVE_SPEED;
			if (currLocation.y < 0) {
				currLocation.y = 0 - currLocation.y;
				movingDown = true;
			}
		}
	}

	void onCollision(CollisionResult collision) override
	{
		movingDown = collision->OtherCenter->x < currLocation.x;
		movingRight = collision->OtherCenter->y < currLocation.y;
	}

private:
	Hitbox* makeHitbox()
	{
		return new SingleHitbox(new MovingCircle([this] {return Point{ currLocation.x + RADIUS, currLocation.y + RADIUS }; }, RADIUS));
	}
};