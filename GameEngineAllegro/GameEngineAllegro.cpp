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
#include "TextBase.cpp"
#include "BouncingCircle.cpp"
#include "SittingSquare.cpp"
#include "MouseFollower.cpp"

int main()
{
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	srand(time(NULL));

	EventLoop mainLoop;
	SharedData data;

	data.displaySize.width = 800;
	data.displaySize.height = 600;
	std::unique_ptr<ALLEGRO_DISPLAY, decltype(&al_destroy_display)> display(al_create_display(data.displaySize.width, data.displaySize.height), &al_destroy_display);
	data.display = display.get();

	auto renderer = std::make_unique<Renderer>(mainLoop, data);
	auto listener = std::make_unique<EventListener>(mainLoop, data);

	std::unique_ptr<Square> square(new Square(mainLoop, data, Point{ 200, 200 }, 200));
	std::unique_ptr<MouseFollower> follower(new MouseFollower(mainLoop, data));


	std::vector<std::unique_ptr<BouncingCircle>> circles;
	for (int i = 0; i < 20; i++) {
		circles.push_back(std::make_unique<BouncingCircle>(mainLoop, data));
	}

	mainLoop.Start();
}
