#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "Bird.h"
#include "simulation.h"

#define MAX_ANGLE 359.9
#define USER_DATA_EYESIGHT 10
#define USER_DATA_SPEED 1

#define PRINT_PAJAROS for (int i = 0; i < 2; i++){ pos = birds[i].getPos(); cout << "POSX:"<<pos.posx << endl; cout << "POSY:"<< pos.posy << endl; cout << "DIR:" << birds[i].getDir() << endl;}
using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	Bird birds[2];
	position pos;
	for (int i = 0; i < 2; i++)
	{
		birds[i].initRandom(USER_DATA_EYESIGHT, USER_DATA_SPEED);
	}
	PRINT_PAJAROS
	for (int k = 0; k < 2; k++)
	{
		birds[k].calculateNewDir(birds, 2);
	}
	for (int j = 0; j < 2; j++)
	{
		birds[j].move();
	}
	PRINT_PAJAROS
	getchar();
	return 0;
}


