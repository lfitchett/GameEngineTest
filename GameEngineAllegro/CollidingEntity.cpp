#pragma once

#include "pch.h"

#include "EventLoop.cpp"
#include "EntityWithData.cpp"
#include "Hitbox.cpp"
#include "HitboxDisplay.cpp"

class CollidingEntity : protected EntityWithData
{
protected:
	Hitbox* hitbox;
	HitboxDisplay hbDisplay;

public:
	CollidingEntity(EventLoop &loop, SharedData& data, Hitbox* hitbox)
		: EntityWithData(data), hbDisplay(loop, *hitbox), hitbox(hitbox)
	{
		sharedData.collisionManager.AddHitbox(hitbox);
	};

	virtual ~CollidingEntity()
	{
		sharedData.collisionManager.RemoveHitbox(hitbox);
		delete hitbox;
	}
};