#include "pch.h"

#include "EntityWithData.cpp"

class BitmapBase : public EntityWithData
{
private:
	Location currLocation;
	ALLEGRO_BITMAP* bitmap = nullptr;

public:
	BitmapBase(EventLoop &loop, SharedData &data, int width, int height, ALLEGRO_COLOR color)
		: EntityWithData(loop, data)
	{
		makeBitmap(width, height, color);
	}

	BitmapBase(EventLoop &loop, SharedData &data, std::string filename)
		: EntityWithData(loop, data)
	{
		loadBitmap(filename);
	}

	~BitmapBase()
	{
		al_destroy_bitmap(bitmap);
	}

	void setLocation(double x, double y)
	{
		currLocation.x = x;
		currLocation.y = y;
	}
	void setLocation(Location loc)
	{
		currLocation.x = loc.x;
		currLocation.y = loc.y;
	}


protected:
	BitmapBase(EventLoop &loop, SharedData &data) : EntityWithData(loop, data) {}

	void Tick()
	{
		al_draw_bitmap(bitmap, currLocation.x, currLocation.y, 0);
	}

	void makeBitmap(int width, int height, ALLEGRO_COLOR color)
	{
		bitmap = al_create_bitmap(width, height);
		if (!bitmap) {
			printf("Failed to make bitmap\n");
		}

		al_set_target_bitmap(bitmap);
		al_clear_to_color(color);
		al_set_target_bitmap(al_get_backbuffer(sharedData.display));
	}

	void loadBitmap(std::string filename)
	{
		bitmap = al_load_bitmap(filename.c_str());
		if (!bitmap) {
			printf("Failed to load bitmap\n");
		}
	}
};
