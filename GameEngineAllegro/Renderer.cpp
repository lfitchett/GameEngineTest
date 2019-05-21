#include "pch.h"

#include <chrono>
#include <thread>
#include <string>

#include "RenderedEntity.cpp"
#include "TextBase.cpp"

using namespace std::chrono;

constexpr int FPS_TARGET = 60;
constexpr nanoseconds TICK_INCREASE = duration_cast<nanoseconds>(seconds(1)) / FPS_TARGET;

class Renderer : public RenderedEntity
{
private:
	time_point<system_clock> lastTickTime;
	double averageFps;
	TextBase fpsMeter;
	nanoseconds threadDelay;

public:
	Renderer(EventLoop &loop, SharedData& data) :RenderedEntity(loop), fpsMeter(loop, data)
	{
		fpsMeter.color = al_map_rgb(250, 218, 94);
		fpsMeter.flags = ALLEGRO_ALIGN_RIGHT;
		fpsMeter.location.x = data.displaySize.width;
		fpsMeter.location.y = 10;

		// Figure out how long thread scheduling takes
		std::this_thread::sleep_for(nanoseconds(100));
		auto targetTime = system_clock::now() + TICK_INCREASE;
		std::this_thread::sleep_until(targetTime);
		threadDelay = system_clock::now() - targetTime;
	}

protected:
	void Render() override
	{
		auto nextTickTime = lastTickTime + TICK_INCREASE - threadDelay;
		std::this_thread::sleep_until(nextTickTime);

		auto fps = duration_cast<nanoseconds>(seconds(1)) / duration_cast<nanoseconds>(system_clock::now() - lastTickTime);
		averageFps = .9 * averageFps + .1 * fps;

		printf("FPS: %.2f / %d\n", averageFps, FPS_TARGET);
		fpsMeter.text = std::to_string(averageFps);

		lastTickTime = system_clock::now();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		printf("refresh\n\n\n");
	}
};
