#include "simulation.h"

void simulation::update(Bird * birds, unsigned int birdCount)
{
	for (int i = 0; i < birdCount; i++)
	{
		birds[i].calculateNewDir(birds, birdCount);
	}
	for (int j = 0; j < birdCount; j++)
	{
		birds[j].move();
	}
}
