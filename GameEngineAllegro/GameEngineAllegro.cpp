// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "SharedData.cpp"
#include "EventLoop.cpp"
#include "CleanupList.cpp"

#include "EventListener.cpp"
#include "Renderer.cpp"
#include "CleanupEntity.cpp"
#include "BitmapBase.cpp"
#include "Text.cpp"
#include "BouncingCircle.cpp"

#include "Polygon.cpp";

int main()
{
	int points[3][2] = { {1,1},{2,2},{3,3} };
	SizedPolygon<3> test1(points);

	auto test2 = test1.Points;

	return 0;
}
