#include "pch.h"

#include <chrono>
#include <thread>

#include "RenderedEntity.cpp"


using namespace std::chrono;

constexpr int FPS_TARGET = 30;
constexpr nanoseconds TICK_INCREASE = duration_cast<nanoseconds>(seconds(1)) / FPS_TARGET;

class Renderer : public RenderedEntity
{
	using RenderedEntity::RenderedEntity;

private:
	time_point<system_clock> lastTickTime;
	double averageFps;

protected:
	void Render() override
	{
		auto nextTickTime = lastTickTime + TICK_INCREASE;
		std::this_thread::sleep_until(nextTickTime);

		auto fps = duration_cast<nanoseconds>(seconds(1)) / duration_cast<nanoseconds>(system_clock::now() - lastTickTime);
		averageFps = .9 * averageFps + .1 * fps;
		printf("FPS: %.2f / %d\n", averageFps, FPS_TARGET);

		lastTickTime = system_clock::now();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		printf("refresh\n\n\n");
	}
};
