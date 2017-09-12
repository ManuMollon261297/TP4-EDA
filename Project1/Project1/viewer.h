#include "Bird.h"
#include <allegro5\allegro.h>
#include <allegro5/allegro_font.h> 

typedef struct  {
	double width;
	double height;
} pic_dim;

class viewer 
{
public:
	viewer(unsigned int width_, unsigned int height_, Bird *birds_, unsigned int bird_count_);
	~viewer();
	void init_allegro(void); // Debe llamarse luego de crear un objeto
	int is_init_ok(void); // Debe llamarse luego de init_allegro()
	void update_display();
	ALLEGRO_DISPLAY *display;

private:
	void set_background(void);
	void set_bird(Bird *pbird);
	pic_dim get_pic_size(ALLEGRO_BITMAP *pic);
	pic_dim set_pic_size(pic_dim reference, double factor);
	position set_pic_center(position reference, double factor);

	position background_ref;
	unsigned int width;
	unsigned int height;
	unsigned int bird_count;
	int ret; // Check de la inicializacion de allegro 
	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *birdPic;
	ALLEGRO_FONT *text;
	Bird *birds;
	//ALLEGRO_FONT *font;
};
