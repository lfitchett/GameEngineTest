#include "pch.h"

#include "EntityWithData.cpp"

class Text : public EntityWithData
{
public:
	Text(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		
	}

	~Text() {
		printf("Cleanup Text\n");
	}

protected:
	void Tick()
	{
		al_draw_text(sharedData.fontManager.GetFont("./Resources/Fonts/arial.ttf", 72), al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
	}
};
