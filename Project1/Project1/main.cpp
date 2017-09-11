#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "Bird.h"
#include "viewer.h"
#include "simulation.h"

#define MAX_ANGLE 359.9
#define USER_DATA_EYESIGHT 10
#define USER_DATA_SPEED 1
#define N_PAJAROS 5

#define PRINT_PAJAROS for (int i = 0; i < N_PAJAROS; i++){ pos = birds[i].getPos(); cout << "POSX:"<<pos.posx << endl; cout << "POSY:"<< pos.posy << endl; cout << "DIR:" << birds[i].getDir() << endl;}
using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	Bird birds[N_PAJAROS];
	position pos;
	for (int i = 0; i < N_PAJAROS; i++)
	{
		birds[i].initRandom(USER_DATA_EYESIGHT, USER_DATA_SPEED);
	}
	PRINT_PAJAROS
	for (int k = 0; k < N_PAJAROS; k++)
	{
		birds[k].calculateNewDir(birds, N_PAJAROS);
	}
	for (int j = 0; j < N_PAJAROS; j++)
	{
		birds[j].move();
	}
	PRINT_PAJAROS
	//Prueba de impresion de pajaros
	viewer view(100, 70, birds, N_PAJAROS);
	view.init_allegro();
	if (!view.is_init_ok()) {
		return -2;
	}
	view.update_display();

	getchar();
	return 0;
}


