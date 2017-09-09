#include <iostream>
#include "Bird.h"
#include "simulation.h"
#include "viewer.h"

int main()
{
	Bird pajaro;
	int aux;
	viewer v(100, 70, &pajaro, 3);
	
	v.init_allegro();
	aux = v.is_init_ok();
	v.update_display();

	al_rest(5.0);
	return 0;
}