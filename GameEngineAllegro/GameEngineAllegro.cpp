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
#include "Wall.cpp"

int main()
{
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	srand(time(NULL));

	EventLoop mainLoop;
	SharedData data;

	data.displaySize.width = 1000;
	data.displaySize.height = 1000;
	std::unique_ptr<ALLEGRO_DISPLAY, decltype(&al_destroy_display)> display(al_create_display(data.displaySize.width, data.displaySize.height), &al_destroy_display);
	data.display = display.get();

	auto renderer = std::make_unique<Renderer>(mainLoop, data);
	auto listener = std::make_unique<EventListener>(mainLoop, data);

	//std::unique_ptr<Rectangle> square(new Rectangle(mainLoop, data, Point{ 100, 400 }, 200));
	std::unique_ptr<MouseFollower> follower(new MouseFollower(mainLoop, data));


	std::vector<std::unique_ptr<BouncingCircle>> circles;
	for (int i = 0; i < 2; i++) {
		//circles.push_back(std::make_unique<BouncingCircle>(mainLoop, data));
	}

	std::vector<std::unique_ptr<Wall>> walls;
	Point ul{ 0,0 };
	Point ur{ 0, (double)data.displaySize.height };
	Point br{ (double)data.displaySize.width, (double)data.displaySize.height };
	Point bl{ (double)data.displaySize.width, 0 };

	walls.push_back(std::make_unique<Wall>(mainLoop, data, ul, ur));
	walls.push_back(std::make_unique<Wall>(mainLoop, data, ur, br));
	walls.push_back(std::make_unique<Wall>(mainLoop, data, br, bl));
	walls.push_back(std::make_unique<Wall>(mainLoop, data, bl, ul));


	walls.push_back(std::make_unique<Wall>(mainLoop, data, Point{ 400, 400 }, Point{ 500, 600 }));
	walls.push_back(std::make_unique<Wall>(mainLoop, data, Point{ 800, 700 }, Point{ 700, 900 }));



	mainLoop.Start();
}
