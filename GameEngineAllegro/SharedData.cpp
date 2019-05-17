#pragma once

#include "pch.h"
#include "FontManager.cpp"
#include "CleanupEntity.cpp"

struct Location {
	double x;
	double y;

	void print() {
		printf("X: %f, Y: %f\n", x, y);
	}
};

struct SharedData {
	ALLEGRO_DISPLAY* display;
	CleanupEntity* cleanup;
	Location mouseClickLocation;
	Location mouseLocation;
	FontManager fontManager;
};