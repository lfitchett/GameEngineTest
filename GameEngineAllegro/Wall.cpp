#include "pch.h"

#include "BitmapBase.cpp"
#include "CollidingEntity.cpp"
#include "UnitVector.cpp"

constexpr double width = 5;

class Wall : TickingEntity<Drawing>
{
private:
	Point start;
	Point end;
	ALLEGRO_COLOR wallColor = al_map_rgb(139, 69, 19);
	CollidingEntity collision;

public:
	Wall(EventLoop &loop, SharedData& data, Point start, Point end) :
		TickingEntity(loop),
		start(start),
		end(end),
		collision(loop, data, [&start, &end] {
			UnitVector angle(start, end);
			Vector offset = angle.ToNorm() * width;

			std::vector<Point> points {
				{start.x + offset.x, start.y + offset.y},
				{start.x - offset.x, start.y - offset.y},
				{end.x - offset.x, end.y - offset.y},
				{end.x + offset.x, end.y + offset.y}
			};

			return new SingleHitbox(new Polygon(points), false);
		}())
	{	}

protected:
	void Tick() override
	{
		al_draw_line(start.x, start.y, end.x, end.y, wallColor, width);
	}

};