#pragma once

#include "pch.h"

#include "EntityWithData.cpp"
#include "RenderedEntity.cpp"

class HitboxDisplay : public EntityWithData, public RenderedEntity
{
private:
	Hitbox* hitbox;
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR* currentColor;

public:
	HitboxDisplay(EventLoop &loop, SharedData &data, Hitbox* hitbox) : EntityWithData(data), RenderedEntity(loop)
	{
		this->hitbox = hitbox;
		currentColor = &green;
	}

	void setIsHit(bool isHit) {
		currentColor = isHit ? &red : &green;
	}

protected:
	void Render() override
	{
		for (size_t i = 0; i < hitbox->GetSize(); i++) {
			Shape* s = hitbox->GetShapes()[i];
			
			if (Circle* c = dynamic_cast<Circle*>(s)) {
				DrawCircle(c);
				continue;
			}
			if (Polygon* p = dynamic_cast<Polygon*>(s)) {
				DrawPolygon(p);
				continue;
			}
		}
	}

	void DrawCircle(Circle* c)
	{
		al_draw_circle(c->GetCenter().x, c->GetCenter().y, c->Radius, *currentColor, 1);
	}

	void DrawPolygon(Polygon* p)
	{
		Point* start = p->GetPoints();
		Point* end = start + p->GetNumPoints() - 1;

		for (Point* p = start; p < end; p++) {
			al_draw_line(p->x, p->y, (p+1)->x, (p+1)->y, *currentColor, 1);
		}
		al_draw_line(end->x, end->y, start->x, start->y, *currentColor, 1);


		//RectangleBound* bounds = p->GetBounds();
		//al_draw_rectangle(bounds->xMin, bounds->yMin, bounds->xMax, bounds->yMax, *currentColor, 1);

	}
};