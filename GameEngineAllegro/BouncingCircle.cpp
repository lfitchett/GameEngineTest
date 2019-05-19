#include "pch.h"

#include "BitmapBase.cpp"
#include "Hitbox.cpp"

constexpr int MOVE_SPEED = 10;
constexpr int BOUNCING_SIZE = 50;

class BouncingCircle : public BitmapBase
{
private:
	bool movingRight = true;
	bool movingDown = true;
	Hitbox* hitbox;

public:
	BouncingCircle(EventLoop &loop, SharedData &data) : BitmapBase(loop, data, "Resources/Images/blueCircle.png")
	{
		setSize(BOUNCING_SIZE, BOUNCING_SIZE);
		setLocation(rand() % sharedData.displaySize.width, rand() % sharedData.displaySize.height);

		hitbox = new SingleHitbox(new ReferenceCircle(currLocation, BOUNCING_SIZE / 2));
		sharedData.collisionManager.AddHitbox(hitbox);
	}

	~BouncingCircle()
	{
		sharedData.collisionManager.RemoveHitbox(hitbox);
		delete hitbox;
	}

protected:
	void Tick()
	{
		if (movingRight) {
			currLocation.x += MOVE_SPEED;
			if (currLocation.x > sharedData.displaySize.width) {
				currLocation.x = 2 * sharedData.displaySize.width - currLocation.x;
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
			if (currLocation.y > sharedData.displaySize.height) {
				currLocation.y = 2 * sharedData.displaySize.height - currLocation.y;
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

		CollisionResult collision = sharedData.collisionManager.FindCollision(hitbox);
		if (collision) {
			movingDown = collision->OtherCenter->x < currLocation.x;
			movingRight = collision->OtherCenter->y < currLocation.y;

			printf("Collision\n");
		}

		BitmapBase::Tick();
	}
};