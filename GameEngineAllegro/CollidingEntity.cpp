#pragma once

#include "pch.h"

#include "EventLoop.cpp"
#include "EntityWithData.cpp"
#include "Hitbox.cpp"
#include "HitboxDisplay.cpp"

class CollidingEntity : public EntityWithData
{
private:
	EventId id;
	HitboxDisplay* hbDisplay;

protected:
	EventLoop &mainLoop;
	Hitbox* hitbox;

	std::function<void(CollisionResult)> onCollision;

public:
	CollidingEntity(EventLoop &loop, SharedData& data, Hitbox* hitbox, std::function<void(CollisionResult)> onCollision)
		: mainLoop(loop), EntityWithData(data), onCollision(onCollision) {
		id = loop.Subscribe([this] { CheckCollision(); }, 1);

		this->hitbox = hitbox;
		sharedData.collisionManager.AddHitbox(hitbox);
		hbDisplay = new HitboxDisplay(mainLoop, sharedData, hitbox);
	};

	virtual ~CollidingEntity() {
		mainLoop.Unsubscribe(id);

		delete hbDisplay;
		sharedData.collisionManager.RemoveHitbox(hitbox);
		delete hitbox;
	}

private:
	void CheckCollision()
	{
		CollisionResult collision = sharedData.collisionManager.FindCollision(hitbox);
		if (collision) {
			printf("Collision\n");
			onCollision(std::move(collision));
		}
	}
};