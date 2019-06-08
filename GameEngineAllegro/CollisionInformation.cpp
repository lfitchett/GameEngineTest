#include "pch.h"

#include "Point.cpp"
#include "UnitVector.cpp"

struct CollisionInformation
{
	UnitVector Direction;
	double overlap;
	bool isOtherMoving;
};