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

int main()
{
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();

	EventLoop mainLoop;
	SharedData data;
	CleanupList cleanup;

	data.displaySize.width = 800;
	data.displaySize.height = 600;
	data.display = al_create_display(data.displaySize.width, data.displaySize.height);

	auto renderer = std::make_unique<Renderer>(mainLoop);
	auto listener = std::make_unique<EventListener>(mainLoop, data);
	auto c1 = std::make_unique<BouncingCircle>(mainLoop, data);
	auto c2 = std::make_unique<BouncingCircle>(mainLoop, data);


	mainLoop.Start();

	cleanup.Cleanup();
	al_destroy_display(data.display);

	return 0;
}
