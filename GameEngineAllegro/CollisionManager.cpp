#include "pch.h"
#include "CollisionManager.h"

#include "HitboxCollision.cpp"

void CollisionManager::AddHitbox(Hitbox* h)
{
	hitboxes.push_back(h);
}

void CollisionManager::RemoveHitbox(Hitbox* h)
{
	for (size_t i = 0; i < hitboxes.size(); i++) {
		if (hitboxes[i] == h) {
			hitboxes.erase(hitboxes.begin() + i);
		}
	}
}

CollisionResult CollisionManager::FindCollision(Hitbox* h1)
{
	CollisionInformation* result;
	for (Hitbox* h2 : hitboxes) {
		if (h2 == h1)
			continue;

		if (result = Collisions::isColliding(*h1, *h2)) {
			result->isOtherMoving = h2->isMoving;
			return CollisionResult(result);
		}
	}

	return false;
}