#pragma once

#include "pch.h"

#include "Point.cpp"
#include "FontManager.cpp"
#include "BitmapManager.cpp"
#include "CollisionManager.h"

struct Size 
{
	uint64_t width;
	uint64_t height;
};

struct SharedData 
{
	ALLEGRO_DISPLAY* display;
	Size displaySize;
	Point mouseClickLocation = Point{ 0,0 };
	Point mouseLocation = Point{ 0,0 };
	FontManager fontManager;
	BitmapManager bitmapManager;
	CollisionManager collisionManager;
};