#include "pch.h"

class BitmapManager {
private:
	std::unordered_map<std::string, std::shared_ptr<ALLEGRO_BITMAP>> bitmaps;

public:
	BitmapManager()
	{
		al_init_image_addon();
		al_init_primitives_addon();
	}

	std::shared_ptr<ALLEGRO_BITMAP> loadBitmap(std::string filename)
	{
		std::shared_ptr<ALLEGRO_BITMAP>& result = bitmaps[filename];
		if (!result) {
			result = wrapBitmap(al_load_bitmap(filename.c_str()));
			if (!result) {
				printf("Failed to load bitmap\n");
			}
		}

		return result;
	}

	std::shared_ptr<ALLEGRO_BITMAP> wrapBitmap(ALLEGRO_BITMAP* btmp)
	{
		return std::shared_ptr<ALLEGRO_BITMAP>(btmp, &al_destroy_bitmap);
	}
};