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

int main()
{
	/*al_init();
	al_init_image_addon();
	al_init_primitives_addon();

	EventLoop mainLoop;
	SharedData data;

	data.displaySize.width = 800;
	data.displaySize.height = 600;
	data.display = al_create_display(data.displaySize.width, data.displaySize.height);

	auto renderer = std::make_unique<Renderer>(mainLoop, data);
	auto listener = std::make_unique<EventListener>(mainLoop, data);
	auto c1 = std::make_unique<BouncingCircle>(mainLoop, data);
	auto c2 = std::make_unique<BouncingCircle>(mainLoop, data);
	auto text = std::make_unique<TextBase>(mainLoop, data);
	text->text = "Test";
	text->location.x = 200;
	text->location.y = 300;

	mainLoop.Start();
	al_destroy_display(data.display);
	*/

	int poly[3][2] = { {1,1},{2,2},{3,3} };
	double x = 5, y = 10;
	auto test = new MovingPolygon<3>([&x, &y] {return Point{ x,y }; }, poly);

	auto a = test->GetCenter();
	x = 10, y = 20;
	auto b = test->GetCenter();



	return 0;
}
