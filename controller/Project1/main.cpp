#include <iostream>
#include <stdio.h>
#include "controller.h"

using namespace std;

int main(void) {

	ALLEGRO_DISPLAY * display;

	controller control1;

	if (!al_init()) {
		return -1;
	}

	control1.justinit(); // solo debe ser llamada 1 sola vez

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_event_queue(control1.event_queue);
		return -1;
	}

	control1.display = display; 
	// controller necesita de un puntero al display para poder cerrarlo
	control1.register_events();
	
	while(control1.isnotexit()){
		control1.update_ctrl();
		printf("randomjigg: %d speed: %d eyesight: %d",control1.randomjiggle,control1.speed, control1.eyesight);
		if (system("CLS")) system("clear");
	}	
	return 0;
}