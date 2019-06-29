#pragma once

#include "pch.h"

struct RectangleBound
{
	double xMax = -DBL_MAX;
	double yMax = -DBL_MAX;
	double xMin = DBL_MAX;
	double yMin = DBL_MAX;

	bool intersects(RectangleBound& other)
	{
		return xMin < other.xMax && xMax > other.xMin && yMin < other.yMax && yMax > other.yMin;
	}
};