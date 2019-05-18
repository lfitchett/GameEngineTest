#include "pch.h"

#include "EntityWithData.cpp"

class Circle : public EntityWithData
{
public:
	Circle(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		bitmap = al_create_bitmap(20, 20);
		if (!bitmap) {
			printf("Failed to make bitmap\n");
		}

		al_set_target_bitmap(bitmap);
		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_set_target_bitmap(al_get_backbuffer(sharedData.display));

		currLocation.x = 400;
		currLocation.y = 300;
	}

	~Circle() 
	{
		al_destroy_bitmap(bitmap);
		printf("Cleanup Circle\n");
	}

private:
	Location currLocation;
	ALLEGRO_BITMAP* bitmap;

protected:
	void Tick()
	{
		currLocation.x = sharedData.mouseLocation.x;
		currLocation.y = sharedData.mouseLocation.y;

		al_draw_bitmap(bitmap, currLocation.x, currLocation.y, 0);
	}
};
