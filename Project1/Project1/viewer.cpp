#include <iostream>
#include "viewer.h"
#include <allegro5\allegro_image.h>
#include <string>

using namespace std;

//viewer::viewer(string path_, unsigned int width_, unsigned int height_, Bird *birds_, unsigned int bird_count_)
//{
//	width = width_;
//	height = height_;
//	birds = birds_;
//	bird_count = bird_count_;
//	ret = 1; // Value por defecto
//	path = path_;
//}

//viewer::~viewer()
//{
//}

void viewer::init_allegro(void)
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		ret = 0;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon !\n");
		ret = 0;
	}

	if (!al_init_font_addon())
	{
		al_shutdown_image_addon();
		fprintf(stderr, "Failed to initialize Font\n");
		ret = 0;
	}

	display = al_create_display(width, height);
	if (!display) {
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		fprintf(stderr, "failed to create display!\n");
		ret = 0;
	}
	
	string background_path;
	background_path.append(path);
	background_path.append("\\cielo.png");
}

int viewer::is_init_ok(void)
{
	return ret;
}

void viewer::update_display()
{
}