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

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);

	ALLEGRO_FONT* font = data.fontManager.GetFont();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
	al_flip_display();
	al_rest(5.0);

	/*data.cleanup = new CleanupEntity(mainLoop);
	cleanup.Add(data.cleanup);

	cleanup.Add(new Renderer(mainLoop, data));
	cleanup.Add(new EventListener(mainLoop, data));
	cleanup.Add(new Circle(mainLoop, data));
	cleanup.Add(new Text(mainLoop, data));



	mainLoop.Start();

	cleanup.Cleanup();*/

	return 0;
}
