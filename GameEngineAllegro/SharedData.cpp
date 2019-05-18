#pragma once

#include "pch.h"
#include "FontManager.cpp"
#include "CleanupEntity.cpp"
#include "Point.cpp"

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
	CleanupEntity* cleanup;
};