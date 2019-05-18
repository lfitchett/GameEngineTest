#pragma once

#include "pch.h"
#include "FontManager.cpp"
#include "CleanupEntity.cpp"

struct Location 
{
	double x = 0;
	double y = 0;

	void print() {
		printf("X: %f, Y: %f\n", x, y);
	}
};

struct Size 
{
	uint64_t width;
	uint64_t height;
};

struct SharedData 
{
	ALLEGRO_DISPLAY* display;
	Size displaySize;
	Location mouseClickLocation;
	Location mouseLocation;
	FontManager fontManager;
	CleanupEntity* cleanup;
};