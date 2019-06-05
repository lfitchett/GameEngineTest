#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr double width = 15;

class Wall : EntityWithData, RenderedEntity
{
private:
	Point start;
	Point end;
	Hitbox* hitbox;
	ALLEGRO_COLOR wallColor = al_map_rgb(0, 0, 255);
	HitboxDisplay* hbDisplay;

public:
	Wall(EventLoop &loop, SharedData& data, Point start, Point end) :
		EntityWithData(data),
		RenderedEntity(loop),
		start(start),
		end(end)
	{
		UnitVector angle(start, end);
		Vector offset = angle.ToNorm() * width;

		double points[4][2] = { 
			{start.x + offset.x, start.y + offset.y},
			{start.x - offset.x, start.y - offset.y},
			{end.x - offset.x, end.y - offset.y},
			{end.x + offset.x, end.y + offset.y}
		};
		hitbox = new SingleHitbox(new SizedPolygon<4>(points), false);
		sharedData.collisionManager.AddHitbox(hitbox);
		hbDisplay = new HitboxDisplay(mainLoop, sharedData, hitbox);

	}

	~Wall()
	{
		sharedData.collisionManager.RemoveHitbox(hitbox);
		delete hitbox;
	}

protected:
	void Render() override
	{
		al_draw_line(start.x, start.y, end.x, end.y, wallColor, width);
	}

};