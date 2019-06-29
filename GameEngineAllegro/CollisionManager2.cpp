#include "pch.h"

#include "Hitbox.cpp"
#include "Circle.cpp"
#include "Polygon.cpp"
#include "CollisionInformation.cpp"

class CollisionManager2
{
private:
	std::unordered_map<Shape*, Hitbox*> hitboxMap;

	std::unordered_set<Polygon*> movingPolygons;
	std::unordered_set<Polygon*> staticPolygons;
	std::unordered_set<Circle*> movingCircles;
	std::unordered_set<Circle*> staticCircles;

public:
	void AddHitbox(Hitbox* hitbox)
	{
		Shape** shapes = hitbox->GetShapes();
		for (size_t i = 0; i < hitbox->GetSize(); i++) 
		{
			if (Circle* c = dynamic_cast<Circle*>(shapes[i])) {
				if (hitbox->isMoving) {
					movingCircles.insert(c);
				}
				else {
					staticCircles.insert(c);
				}
			}
			else if (Polygon* p = dynamic_cast<Polygon*>(shapes[i])) {
				if (hitbox->isMoving) {
					movingPolygons.insert(p);
				}
				else {
					staticPolygons.insert(p);
				}
			}
			else {
				throw std::runtime_error("Unknown shape");
			}
		}
	}


	
};