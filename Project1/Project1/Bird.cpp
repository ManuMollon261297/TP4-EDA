#include "Bird.h"
#include <cmath>

unsigned int Bird::xMax=100;
unsigned int Bird::yMax=70;

Bird::Bird(void)
{
	eyesight = 0;
	maxRandomJiggle = 3;
	speed = 1;
	currentDir = 0;
	p.posx = 0;
	p.posy = 0;
	newDir = 0;
}

void Bird::SetGlobalXYMax(unsigned int xMax_, unsigned int yMax_)
{
	xMax = xMax_;
	yMax = yMax_;
}

void Bird::calculateNewDir(Bird * birds, unsigned int birdCount)
{
	unsigned int birdsInSight = 0;
	double AngleSum = 0;
	for (unsigned int i = 0; i < birdCount; i++)
	{
		if (isBirdInSight(birds + i))
		{
			AngleSum += (birds + i)->currentDir;
			birdsInSight++;
		}
		else
		{
			//nothing
		}
	}
	if (birdsInSight > 1)
	{
		AngleSum += maxRandomJiggle;
	}
	newDir = AngleSum / ((double)birdsInSight); // birdsInSight deberia ser por lo menos uno, porque el propio pajaro siempre se ve a si mismo
}												// por lo que nunca se divide por cero

void Bird::move(void)
{
//	for (int i = 0; i < speed; i++)
	if(speed>=1)
	{
		position newP;
		double angle_deg = newDir;
		double angle_rad = deg2rad(angle_deg);
		newP.posx = p.posx + (cos(angle_rad)  /50.0); // revisar
		newP.posy = p.posy + (sin(angle_rad) / 50.0);
		if (((newP.posx) > xMax) || ((newP.posy) > yMax) || ((newP.posx) < 0) || ((newP.posy) < 0))
		{
			if (newP.posx > xMax)
			{
				newP.posx -= xMax;
				if ((newP.posy > yMax))
				{
					newP.posy -= yMax;
				}
				else if ((newP.posy < 0))
				{
					newP.posy += yMax;
				}

			}
			else if (newP.posx < 0)
			{
				newP.posx += xMax;
				if ((newP.posy > yMax))
				{
					newP.posy -= yMax;
				}
				else if ((newP.posy < 0))
				{
					newP.posy += yMax;
				}
			}
			else if(newP.posy > yMax)
			{
				newP.posy -= yMax;
			}
			else if (newP.posy < 0)
			{
				newP.posy += yMax;
			}
		}
		p.posx = newP.posx;
		p.posy = newP.posy;
		currentDir = newDir;
		//newDir = 0;
	}
}

void Bird::incrementEyesight(void)
{
	eyesight++;
}

bool Bird::decrementEyesight(void)
{
	if (eyesight > 0)
	{
		eyesight--;
		return true;
	}
	else
	{
		return false;
	}
}

void Bird::incrementSpeed(void)
{
	speed++;
}

bool Bird::decrementSpeed(void)
{
	if (speed> 0)
	{
		speed--;
		return true;
	}
	else
	{
		return false;
	}
}

void Bird::incrementMaxRandomJiggle(void)
{
	maxRandomJiggle++;
}

bool Bird::decrementMaxRandomJiggle(void)
{
	if (maxRandomJiggle > 0)
	{
		maxRandomJiggle--;
		return true;
	}
	else
	{
		return false;
	}
}

position Bird::getPos(void)
{
	return p;
}

double Bird::getDir(void)
{
	return currentDir;
}

double Bird::getEyesight(void)
{
	return eyesight;
}

double Bird::getMaxRandomJiggle(void)
{
	return maxRandomJiggle;
}

bool Bird::isBirdInSight(Bird * bird)
{
	bool birdFound = false;
	double distancia[9];
	position pos = bird->getPos();
	distancia[0] = sqrt((p.posx - pos.posx)*(p.posx - pos.posx) + (p.posy - pos.posy)*(p.posy - pos.posy)); //echo // las nueve distancias posibles en una superificie toroidal
	distancia[1] = sqrt((p.posx - (pos.posx- xMax))*(p.posx - (pos.posx - xMax)) + (p.posy - (yMax + pos.posy))*(p.posy - (yMax + pos.posy))); //echo
	distancia[2] = sqrt((p.posx - pos.posx)*(p.posx - pos.posx) + (p.posy - (yMax + pos.posy))*(p.posy - (yMax + pos.posy))); // echo
	distancia[3] = sqrt((p.posx - (pos.posx + xMax))*(p.posx - (pos.posx + xMax)) + (p.posy - (yMax + pos.posy))*(p.posy - (yMax + pos.posy))); //echo
	distancia[4] = sqrt((p.posx - (pos.posx - xMax))*(p.posx - (pos.posx - xMax)) + (p.posy - pos.posy)*(p.posy - pos.posy)); //echo
	distancia[5] = sqrt((p.posx - (pos.posx + xMax))*(p.posx - (pos.posx + xMax)) + (p.posy - pos.posy)*(p.posy - pos.posy)); //echo
	distancia[6] = sqrt((p.posx - pos.posx)*(p.posx - pos.posx) + (p.posy - (pos.posy - yMax))*(p.posy - (pos.posy - yMax))); // echo
	distancia[7] = sqrt((p.posx - (pos.posx - xMax))*(p.posx - (pos.posx - xMax)) + (p.posy - (pos.posy - yMax))*(p.posy - (pos.posy - yMax))); //echo
	distancia[8] = sqrt((p.posx - (pos.posx + xMax))*(p.posx - (pos.posx + xMax)) + (p.posy - (pos.posy - yMax))*(p.posy - (pos.posy - yMax))); //echo
	double smallest = distancia[0];
	for (int i = 1; i < 9; ++i)
	{
		if (distancia[i] < smallest)
		{
			smallest = distancia[i]; // distanica va de 0 a 8, i nunca es mayor a 8
		}
	}
	if (smallest <= eyesight)
	{
		birdFound = true;
	}
	return birdFound;
}


double Bird::deg2rad(double angulo_deg)
{
	static const double pi = atan(1) * 4;
	return ((angulo_deg*pi) / 180.0);
}

void Bird::initRandom(unsigned int udEyesight, unsigned int udSpeed)
{
	currentDir = (double)(rand()) / ((double)(RAND_MAX /359.999));
	p.posx = (double)(rand()) / ((double)(RAND_MAX / xMax));
	p.posy = (double)(rand()) / ((double)(RAND_MAX / yMax));
	speed = udSpeed;
	eyesight = udEyesight;
}

double Bird::getSpeed(void)
{
	return speed;
}