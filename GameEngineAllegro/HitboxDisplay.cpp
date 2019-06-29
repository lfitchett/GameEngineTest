#pragma once

#include "pch.h"

#include "EntityWithData.cpp"
#include "TickingEntity.cpp"

class HitboxDisplay : public TickingEntity<Rendering>
{
private:
	Hitbox* hitbox;
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR* currentColor;

public:
	HitboxDisplay(EventLoop &loop, Hitbox* hitbox) : TickingEntity(loop)
	{
		this->hitbox = hitbox;
		currentColor = &green;
	}

	void setIsHit(bool isHit) {
		currentColor = isHit ? &red : &green;
	}

protected:
	void Tick() override
	{
		for (size_t i = 0; i < hitbox->GetSize(); i++) {
			Shape* s = hitbox->GetShapes()[i];
			
			if (Circle* c = dynamic_cast<Circle*>(s)) {
				DrawCircle(*c);
				continue;
			}
			if (Polygon* p = dynamic_cast<Polygon*>(s)) {
				DrawPolygon(*p);
				continue;
			}
		}
	}

	void DrawCircle(Circle& circ)
	{
		al_draw_circle(circ.center.x, circ.center.y, circ.radius, *currentColor, 1);
		//al_draw_rectangle(c.x + circ->radius, c.y + circ->radius, c.x - circ->radius, c.y - circ->radius, *currentColor, 1);
		
	}

	void DrawPolygon(Polygon& poly)
	{
		std::vector<Point>& points = poly.GetPoints();

		std::vector<Point>::iterator p = points.begin();
		std::vector<Point>::iterator prev = --points.end();
		while (p != points.end()) {
			al_draw_line(p->x, p->y, prev->x, prev->y, *currentColor, 1);
			prev = p++;
		}
		

		/*RectangleBound* bounds = poly->GetBounds();
		al_draw_rectangle(bounds->xMin, bounds->yMin, bounds->xMax, bounds->yMax, *currentColor, 1);*/

	}
};