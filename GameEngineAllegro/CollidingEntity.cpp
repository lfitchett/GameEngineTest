#pragma once

#include "pch.h"

#include "EventLoop.cpp"
#include "EntityWithData.cpp"
#include "Hitbox.cpp"
#include "HitboxDisplay.cpp"

class CollidingEntity : public EntityWithData, TickingEntity<CollisionDetection>
{
private:
	HitboxDisplay* hbDisplay;

protected:
	EventLoop &mainLoop;
	Hitbox* hitbox;

	std::function<void(CollisionInformation*)> onCollision;

public:
	CollidingEntity(EventLoop &loop, SharedData& data, Hitbox* hitbox, std::function<void(CollisionInformation*)> onCollision)
		: mainLoop(loop), EntityWithData(data), onCollision(onCollision), TickingEntity(mainLoop)
	{
		this->hitbox = hitbox;
		sharedData.collisionManager.AddHitbox(hitbox);
		hbDisplay = new HitboxDisplay(mainLoop, sharedData, hitbox);
	};

	virtual ~CollidingEntity() {
		delete hbDisplay;
		sharedData.collisionManager.RemoveHitbox(hitbox);
		delete hitbox;
	}

private:
	void Tick()
	{
		CollisionResult collision = sharedData.collisionManager.FindCollision(hitbox);
		if (collision) {
			// printf("Collision\n");
			hbDisplay->setIsHit(true);
			onCollision(collision.get());
		}
		else {
			hbDisplay->setIsHit(false);
		}
	}
};