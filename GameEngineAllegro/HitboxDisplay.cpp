#pragma once

#include "pch.h"

#include "EntityWithData.cpp"

class HitboxDisplay : public EntityWithData
{
private:
	Hitbox* hitbox;
	ALLEGRO_COLOR color = al_map_rgb(255, 0, 0);

public:
	HitboxDisplay(EventLoop &loop, SharedData &data, Hitbox* hitbox) : EntityWithData(loop, data)
	{
		this->hitbox = hitbox;
	}

protected:
	void Tick() override
	{
		for (size_t i = 0; i < hitbox->GetSize(); i++) {
			Shape* s = hitbox->GetShapes()[i];
			
			if (Circle* c = dynamic_cast<Circle*>(s)) {
				DrawCircle(c);
				continue;
			}
			if (Polygon* p = dynamic_cast<Polygon*>(s)) {

			}
		}
	}

	void DrawCircle(Circle* c)
	{
		al_draw_circle(c->GetCenter().x, c->GetCenter().y, c->Radius, color, 1);
	}
};