#pragma once

#include "pch.h"

#include "EntityWithData.cpp"
#include "TickingEntity.cpp"

class BitmapBase : public EntityWithData, public TickingEntity<Drawing>
{
private:
	Size size;

protected:
	ALLEGRO_BITMAP* bitmap = nullptr;

public:
	Point location;

	BitmapBase(EventLoop &loop, SharedData &data, int width, int height, ALLEGRO_COLOR color)
		: EntityWithData(data), TickingEntity(loop)
	{
		makeBitmap(width, height, color);
	}

	BitmapBase(EventLoop &loop, SharedData &data, std::string filename)
		: EntityWithData(data), TickingEntity(loop)
	{
		loadBitmap(filename);
	}

	virtual ~BitmapBase()
	{
		al_destroy_bitmap(bitmap);
	}

	void setLocation(double x, double y)
	{
		location.x = x;
		location.y = y;
	}

	Size GetSize()
	{
		return size;
	}

	void setSize(int newWidth, int newHeight)
	{
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(newWidth, newHeight);
		al_set_target_bitmap(newBitmap);
		al_draw_scaled_bitmap(bitmap, 0, 0, size.width, size.height, 0, 0, newWidth, newHeight, 0);
		al_set_target_bitmap(al_get_backbuffer(sharedData.display));

		size.width = newWidth;
		size.height = newHeight;
		al_destroy_bitmap(bitmap);
		bitmap = newBitmap;
	}

	/* Not working well yet */
	void rotate(float radians)
	{
		float extraSize = 1 / cos(radians);

		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(size.width * extraSize, size.height * extraSize);
		al_set_target_bitmap(newBitmap);
		al_draw_rotated_bitmap(bitmap, size.width / 2, size.height / 2, size.width / 2, size.height / 2, radians, 0);
		al_set_target_bitmap(al_get_backbuffer(sharedData.display));
		
		al_destroy_bitmap(bitmap);
		bitmap = newBitmap;
		size.width *= extraSize;
		size.height *= extraSize;
	}

protected:
	BitmapBase(EventLoop &loop, SharedData &data) : EntityWithData(data), TickingEntity(loop) {}

	void Tick() override
	{
		al_draw_bitmap(bitmap, location.x, location.y, 0);
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

		size.width = width;
		size.height = height;
	}

	void loadBitmap(std::string filename)
	{
		bitmap = al_load_bitmap(filename.c_str());
		if (!bitmap) {
			printf("Failed to load bitmap\n");
		}

		size.width = al_get_bitmap_width(bitmap);
		size.height = al_get_bitmap_height(bitmap);
	}
};
