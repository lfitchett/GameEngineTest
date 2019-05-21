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
	CleanupList<void*> cleanup;

	data.displaySize.width = 800;
	data.displaySize.height = 600;
	data.display = al_create_display(data.displaySize.width, data.displaySize.height);

	data.cleanup = new CleanupEntity(mainLoop);
	cleanup.Add(data.cleanup);

	cleanup.Add(new Renderer(mainLoop));
	cleanup.Add(new EventListener(mainLoop, data));
	//cleanup.Add(new Text(mainLoop, data));
	cleanup.Add(new BouncingCircle(mainLoop, data));
	cleanup.Add(new BouncingCircle(mainLoop, data));


	mainLoop.Start();

	cleanup.Cleanup();
	al_destroy_display(data.display);

	return 0;
}
