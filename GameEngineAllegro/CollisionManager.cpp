#pragma once

#include "pch.h"

#include <vector>
#include "Polygon.cpp"


class CollisionManager
{
private:
	std::vector<Polygon*> polygons;



public:
	bool FindCollision(Polygon* p1)
	{
		for (Polygon* p2 : polygons) {



		}
	}
};