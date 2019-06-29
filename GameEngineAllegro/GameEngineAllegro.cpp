// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "SharedData.cpp"
#include "EventLoop.cpp"
#include "EventListener.cpp"
#include "Renderer.cpp"
#include "BitmapBase.cpp"
#include "TextBase.cpp"
#include "BouncingCircle.cpp"
#include "SittingSquare.cpp"
#include "MouseFollower.cpp"
#include "Wall.cpp"

#include "ThreadedObservable.cpp"

int main()
{
	srand(time(NULL));

	ThreadedObservable observe;

	std::vector<Subscription> Subscriptions;
	for (int i = 0; i < 200; i++) {
		Subscriptions.emplace_back(observe, [] {
		});
	}

	for (int i = 0; i < 10000000; i++) {
		observe.on();

		if (i % 1000 == 0) {
			std::cout << i << std::endl;
		}
	}
}
