#pragma once

#include "pch.h"

struct RectangleBound
{
	double xMax;
	double yMax;
	double xMin;
	double yMin;

	RectangleBound() : xMax{ -DBL_MAX }, yMax{ -DBL_MAX }, xMin{ DBL_MAX }, yMin{ DBL_MAX }	{}
	RectangleBound(double xMax, double yMax, double xMin, double yMin)
		: xMax{ xMax }, yMax{ yMax }, xMin{ xMin }, yMin{ yMin }	{}


	bool intersects(RectangleBound& other)
	{
		return xMin < other.xMax && xMax > other.xMin && yMin < other.yMax && yMax > other.yMin;
	}
};