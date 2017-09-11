#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "viewer.h"
#include "simulation.h"
#include "controller.h"

#define MAX_ANGLE 359.9
#define USER_DATA_EYESIGHT 10
#define USER_DATA_SPEED 1
#define N_PAJAROS 5

#define PRINT_PAJAROS for (int i = 0; i < N_PAJAROS; i++){ pos = birds[i].getPos(); cout << "POSX:"<<pos.posx << endl; cout << "POSY:"<< pos.posy << endl; cout << "DIR:" << birds[i].getDir() << endl;}
using namespace std;

//int main()
//{
//	srand((unsigned)time(NULL));
//	Bird birds[N_PAJAROS];
//	position pos;
//	for (int i = 0; i < N_PAJAROS; i++)
//	{
//		birds[i].initRandom(USER_DATA_EYESIGHT, USER_DATA_SPEED);
//	}
//	PRINT_PAJAROS
//	for (int k = 0; k < N_PAJAROS; k++)
//	{
//		birds[k].calculateNewDir(birds, N_PAJAROS);
//	}
//	for (int j = 0; j < N_PAJAROS; j++)
//	{
//		birds[j].move();
//	}
//	PRINT_PAJAROS
//	//Prueba de impresion de pajaros
//	viewer view(100, 70, birds, N_PAJAROS);
//	view.init_allegro();
//	if (!view.is_init_ok()) {
//		return -2;
//	}
//	view.update_display();
//
//	getchar();
//	return 0;
//}

int main()
{
	ALLEGRO_DISPLAY * display;
	//Prueba de impresion de pajaros
		/*viewer view(100, 70, birds, N_PAJAROS);
		view.init_allegro();
		if (!view.is_init_ok()) {
			return -2;
		}
		view.update_display();*/


	srand((unsigned)time(NULL));
	Bird birds[N_PAJAROS];
	position pos;
	for (int i = 0; i < N_PAJAROS; i++)
	{
		birds[i].initRandom(USER_DATA_EYESIGHT, USER_DATA_SPEED);
	}

	controller control1;
	control1.birds = birds;
	control1.birdcount = N_PAJAROS;

	simulation sim;

	if (!al_init()) {
		return -1;
	}


	if (control1.justinit()) {
		return -1;
	} // solo debe ser llamada 1 sola vez

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		control1.destroy_controller_utils();
		return -1;
	}

	control1.display = display;
	// controller necesita de un puntero al display para poder cerrarlo
	if (control1.register_events()) {
		return -1;
	}

	while (control1.isnotexit()) {
		control1.update_ctrl();
		sim.update(birds, N_PAJAROS);

		//printf("randomjigg: %f speed: %f eyesight: %f", birds->getMaxRandomJiggle(), birds->getSpeed(), birds->getEyesight());
		PRINT_PAJAROS
		if (system("CLS")) system("clear");
	}

	control1.destroy_controller_utils();
	al_destroy_display(display);
	return 0;
}