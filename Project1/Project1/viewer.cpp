#include <iostream>
#include "viewer.h"
#include <allegro5\allegro_image.h>
#include <string.h>

#define BIRD_FACTOR 0.1
#define BKG_FACTOR 6
#define DISP_W 640
#define DISP_H 480

viewer::viewer(unsigned int width_, unsigned int height_, Bird *birds_, unsigned int bird_count_)
{
	width = width_;
	height = height_;
	birds = birds_;
	bird_count = bird_count_;
	ret = 1; // Value por defecto
}

viewer::~viewer()
{
	al_destroy_display(display);
	al_destroy_bitmap(background);
	al_destroy_bitmap(birdPic);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
}

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
	
	background = al_load_bitmap("Images/cielo.png");
	if (!background) {
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		fprintf(stderr, "failed to create display!\n");
		ret = 0;
	}

	birdPic = al_load_bitmap("Images/bird.png");
	if (!birdPic) {
		al_destroy_bitmap(background);
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		fprintf(stderr, "failed to create display!\n");
		ret = 0;
	}

	display = al_create_display(DISP_W, DISP_H);
	if (!display) {
		al_destroy_bitmap(background);
		al_destroy_bitmap(birdPic);
		al_shutdown_image_addon();
		al_shutdown_font_addon();
		fprintf(stderr, "failed to create display!\n");
		ret = 0;
	}

}

int viewer::is_init_ok(void)
{
	return ret;
}

void viewer::update_display()
{
	set_background();

	for (unsigned int i = 0; i < bird_count; i++) {
		set_bird(&birds[i]);
	}
	
	al_flip_display();
}

void viewer::set_background(void)
{
	pic_dim sky_dim, sky_newDim;
	pic_dim basic_dim;
	basic_dim.width = width;
	basic_dim.height = height;

	sky_dim = get_pic_size(background);
	sky_newDim = set_pic_size(basic_dim, BKG_FACTOR);

	background_ref.posx = (DISP_W / 2) - (sky_newDim.width / 2);
	background_ref.posy = (DISP_H / 2) - (sky_newDim.height / 2);

	al_draw_scaled_bitmap(background,
		                  0, 0, sky_dim.width, sky_dim.height, 
		                  background_ref.posx, background_ref.posy, sky_newDim.width, sky_newDim.height, 0);
}

void viewer::set_bird(Bird *pbird)
{
	position bird_shift, birdPic_center;
	pic_dim bird_dim, bird_newDim;

	bird_dim = get_pic_size(birdPic);

	bird_newDim = set_pic_size(bird_dim, BIRD_FACTOR);

	bird_shift.posx = (bird_newDim.width) / 2;
	bird_shift.posy = (bird_newDim.height) / 2;

	birdPic_center = set_pic_center(pbird->getPos(), BKG_FACTOR);

	birdPic_center.posx += (background_ref.posx - bird_shift.posx);
	birdPic_center.posy += (background_ref.posy - bird_shift.posy);
	
	//birdPic_center.posx = (DISP_W / 2) - (bird_shift.posx);
	//birdPic_center.posy = (DISP_H / 2) - (bird_shift.posy);

	al_draw_scaled_bitmap(birdPic, 
						  0, 0, bird_dim.width, bird_dim.height, 
						  birdPic_center.posx, birdPic_center.posy, bird_newDim.width, bird_newDim.height, 0);
}

pic_dim viewer::get_pic_size(ALLEGRO_BITMAP * pic)
{
	pic_dim aux;

	aux.width = al_get_bitmap_width(pic);
	aux.height = al_get_bitmap_height(pic);

	return aux;
}

pic_dim viewer::set_pic_size(pic_dim reference, double factor)
{
	pic_dim aux;

	aux.width = reference.width * factor;
	aux.height = reference.height * factor;

	return aux;
}

position viewer::set_pic_center(position reference, double factor)
{
	position aux;

	aux.posx = reference.posx * factor;
	aux.posy = reference.posy * factor;

	return aux;
}
