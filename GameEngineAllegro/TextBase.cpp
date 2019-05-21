#pragma once

#include "pch.h"

#include "EntityWithData.cpp"
#include "RenderedEntity.cpp"

class TextBase : public EntityWithData, public RenderedEntity
{
public:
	ALLEGRO_COLOR color = al_map_rgb(200, 0, 0);
	std::string font = "./Resources/Fonts/arial.ttf";
	uint16_t fontSize = 12;
	Point location;
	uint16_t flags = 0;
	std::string text;

	TextBase(EventLoop &loop, SharedData &data) : EntityWithData(data), RenderedEntity(loop) {	}

protected:
	void Render() override
	{
		al_draw_text(sharedData.fontManager.GetFont(font, fontSize), color, location.x, location.y, flags, text.c_str());
	}
};
