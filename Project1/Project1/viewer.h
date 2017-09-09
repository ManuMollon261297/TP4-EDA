#include "Bird.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>

class viewer 
{
public:
	viewer(char *path_, unsigned int width_, unsigned int height_, Bird *birds_, unsigned int bird_count_) {
		width = width_;
		height = height_;
		birds = birds_;
		bird_count = bird_count_;
		ret = 1; // Value por defecto
		path = path_;
	}
	//~viewer();
	void init_allegro(void); // Debe llamarse luego de crear un objeto
	int is_init_ok(void); // Debe llamarse luego de init_allegro()
	void update_display();

private:
	unsigned int width;
	unsigned int height;
	unsigned int bird_count;
	char *path;
	int ret; // Check de la inicializacion de allegro 
	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *birdPic;
	Bird *birds;
	ALLEGRO_DISPLAY *display;
	//ALLEGRO_FONT *font;
};
