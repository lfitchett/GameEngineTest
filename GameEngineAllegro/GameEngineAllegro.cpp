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

int main()
{
	al_init();

	EventLoop mainLoop;
	SharedData data;
	CleanupList<TickingEntity*> cleanup;

	data.display = al_create_display(800, 600);

	data.cleanup = new CleanupEntity(mainLoop);
	cleanup.Add(data.cleanup);

	cleanup.Add(new Renderer(mainLoop, data));
	cleanup.Add(new EventListener(mainLoop, data));
	cleanup.Add(new Text(mainLoop, data));
	cleanup.Add(new BitmapBase(mainLoop, data, 20, 20, al_map_rgb(255, 0, 255)));



	mainLoop.Start();

	cleanup.Cleanup();
	al_destroy_display(data.display);

	return 0;
}
