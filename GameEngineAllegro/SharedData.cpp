#pragma once

#include "pch.h"

#include "Point.cpp"
#include "FontManager.cpp"
#include "CollisionManager.h"
#include "CleanupEntity.cpp"

struct Size 
{
	uint64_t width;
	uint64_t height;
};

struct SharedData 
{
	ALLEGRO_DISPLAY* display;
	Size displaySize;
	Point mouseClickLocation;
	Point mouseLocation;
	FontManager fontManager;
	CollisionManager collisionManager;
	CleanupEntity* cleanup;
};