#include "pch.h"

#include "BitmapBase.cpp"
#include "Hitbox.cpp"
#include "HitboxDisplay.cpp"

constexpr int MOVE_SPEED = 10;
constexpr int RADIUS = 50;

class BouncingCircle : public BitmapBase
{
private:
	bool movingRight = true;
	bool movingDown = true;
	Hitbox* hitbox;
	HitboxDisplay* hbDisplay;

public:
	BouncingCircle(EventLoop &loop, SharedData &data) : BitmapBase(loop, data, "Resources/Images/blueCircle.png")
	{
		setSize(RADIUS * 2, RADIUS * 2);
		setLocation(rand() % sharedData.displaySize.width, rand() % sharedData.displaySize.height);

		hitbox = new SingleHitbox(new MovingCircle([this] {return Point{ currLocation.x + RADIUS, currLocation.y + RADIUS }; }, RADIUS));
		sharedData.collisionManager.AddHitbox(hitbox);

		hbDisplay = new HitboxDisplay(loop, data, hitbox);
	}

	~BouncingCircle()
	{
		delete hbDisplay;
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