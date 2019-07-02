#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Hitbox& h1, Hitbox& h2)
{
	CollisionInformation* result;

	for (size_t i = 0; i < h1.GetSize(); i++) {
		Shape* s1 = h1.GetShapes()[i];
		for (size_t j = 0; j < h2.GetSize(); j++) {
			Shape* s2 = h2.GetShapes()[j];

			if (result = isColliding(s1, s2)) {
				return result;
			}
		}
	}

	return false;
}