#include "pch.h"

#include <chrono>
#include <thread>
#include <string>

#include "RenderedEntity.cpp"
#include "TextBase.cpp"

using namespace std::chrono;

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

		lastTickTime = system_clock::now();
	}

protected:
	void Render() override
	{
		auto fps = duration_cast<nanoseconds>(seconds(1)) / duration_cast<nanoseconds>(system_clock::now() - lastTickTime);
		averageFps = .9 * averageFps + .1 * fps;
		fpsMeter.text = std::to_string(averageFps);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		lastTickTime = system_clock::now();
		//printf("refresh\n\n\n");
	}
};
