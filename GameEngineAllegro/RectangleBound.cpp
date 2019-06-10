#pragma once

#include "pch.h"

struct RectangleBound
{
	double xMax = -DBL_MAX;
	double yMax = -DBL_MAX;
	double xMin = DBL_MAX;
	double yMin = DBL_MAX;

	bool intersects(RectangleBound* other)
	{
		return this->xMin < other->xMax && this->xMax > other->xMin && this->yMin < other->yMax && this->yMax > other->yMin;
	}
};