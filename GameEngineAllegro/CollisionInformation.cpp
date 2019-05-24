#include "pch.h"

#include "Point.cpp"
#include "UnitVector.cpp"

struct CollisionInformation
{
	Point OtherCenter;
	UnitVector Direction;
	double overlap;
	bool isOtherMoving;
};