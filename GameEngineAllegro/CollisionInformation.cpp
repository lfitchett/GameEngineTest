#include "pch.h"

#include "Point.cpp"

struct CollisionInformation
{
	Point* OtherCenter;

	~CollisionInformation()
	{
		delete OtherCenter;
	}
};