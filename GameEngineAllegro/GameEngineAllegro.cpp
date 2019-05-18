// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "SharedData.cpp"
#include "EventLoop.cpp"
#include "CleanupList.cpp"

#include "EventListener.cpp"
#include "Renderer.cpp"
#include "CleanupEntity.cpp"
#include "Circle.cpp"
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
	cleanup.Add(new Circle(mainLoop, data));
	cleanup.Add(new Text(mainLoop, data));



	mainLoop.Start();

	cleanup.Cleanup();
	al_destroy_display(data.display);

	return 0;
}
