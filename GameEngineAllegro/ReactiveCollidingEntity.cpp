#pragma once

#include "pch.h"

#include "CollidingEntity.cpp"

class ReactiveCollidingEntity : CollidingEntity, TickingEntity<CollisionDetection>
{
private:
	std::function<void(CollisionInformation&)> onCollision;

public:
	ReactiveCollidingEntity(EventLoop &loop, SharedData& data, Hitbox* hitbox, std::function<void(CollisionInformation&)> onCollision)
		: CollidingEntity(loop, data, hitbox), TickingEntity(loop), onCollision(onCollision)
	{	}

	void Tick() override
	{
		CollisionResult collision = sharedData.collisionManager.FindCollision(hitbox);
		if (collision) {
			hbDisplay.setIsHit(true);
			onCollision(*(collision.get()));
		}
		else {
			hbDisplay.setIsHit(false);
		}
	}
};