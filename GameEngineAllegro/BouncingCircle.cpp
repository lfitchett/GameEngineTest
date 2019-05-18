#include "pch.h"

#include "BitmapBase.cpp"

constexpr int MOVE_SPEED = 10;

class BouncingCircle : public BitmapBase
{
private:
	bool movingRight = true;
	bool movingDown = true;

public:
	BouncingCircle(EventLoop &loop, SharedData &data) : BitmapBase(loop, data, "Resources/Images/blueCircle.png") 
	{
		setSize(30, 30);
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

		BitmapBase::Tick();
	}
};