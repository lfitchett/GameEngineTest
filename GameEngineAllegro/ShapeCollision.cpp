#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Shape* s1, Shape* s2)
{
	if (Ellipse* c1 = dynamic_cast<Ellipse*>(s1)) {
		if (Ellipse* c2 = dynamic_cast<Ellipse*>(s2)) {
			return isColliding(c1, c2);
		}

		if (Polygon* p2 = dynamic_cast<Polygon*>(s2)) {
			return isColliding(c1, p2);
		}
	}
	if (Polygon* p1 = dynamic_cast<Polygon*>(s1)) {
		if (Ellipse* c2 = dynamic_cast<Ellipse*>(s2)) {
			return isColliding(p1, c2);
		}

		if (Polygon* p2 = dynamic_cast<Polygon*>(s2)) {
			return isColliding(p1, p2);
		}
	}

	return false;
}