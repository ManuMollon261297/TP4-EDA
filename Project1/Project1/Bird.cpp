#include "Bird.h"
#include <cmath>


Bird::Bird(unsigned int eyesight_ = 0, unsigned int maxRandomJiggle_ = 0, unsigned int speed_ = 5)
{
	eyesight = eyesight_;
	maxRandomJiggle = maxRandomJiggle_;
	speed = speed_;
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
	for (int i = 0; i < birdCount; i++)
	{
		if (isBirdInSight(birds + i))
		{
			AngleSum += (birds + i)->currentDir;
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
	for (int i = 0; i < speed; i++)
	{
		position newP;
		double angle_deg = currentDir;
		double angle_rad = deg2rad(angle_deg);
		newP.posx = p.posx + cos(angle_rad);
		newP.posy = p.posy + sin(angle_rad);
		if (((newP.posx) > xMax) || ((newP.posy) > yMax) || ((newP.posx) < 0) || ((newP.posy) < 0))
		{
			if (newP.posx > xMax)
			{
				newP.posx = p.posx - xMax;
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
				newP.posy += yMax;
			}
			else if (newP.posy < 0)
			{
				newP.posy -= yMax;
			}
		}
		p.posx = newP.posx;
		p.posy = newP.posy;
		currentDir = newDir;
		newDir = 0;
	}
}

void Bird::incrementEyesight(void)
{
	eyesight++;
}

void Bird::decrementEyesight(void)
{
	eyesight--;
}

void Bird::incrementSpeed(void)
{
	speed++;
}

void Bird::decrementSpeed(void)
{
	speed--;
}

void Bird::incrementMaxRandomJiggle(void)
{
	maxRandomJiggle++;
}

void Bird::decrementMaxRandomJigggle(void)
{
	maxRandomJiggle--;
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
	position pos = bird->getPos;
	distancia[0] = sqrt((p.posx - pos.posx)*(p.posx - pos.posx) + (p.posy - pos.posy)*(p.posy - pos.posy)); //echo // las nueve distancias posibles en una superificie toroidal
	distancia[1] = sqrt((p.posx - (pos.posx- xMax))*(p.posx - (pos.posx - xMax)) + (p.posy - (yMax + pos.posy))*(p.posy - (yMax + pos.posy))); //echo
	distancia[2] = sqrt((p.posx - pos.posx)*(p.posx - pos.posx) + (p.posy - (yMax + pos.posy))*(p.posy - (yMax + pos.posy))); // echo
	distancia[3] = sqrt((p.posx - (pos.posx + xMax))*(p.posx - (pos.posx + xMax)) + (p.posy - (yMax + pos.posy))*(p.posy - (yMax + pos.posy))); //echo
	distancia[4] = sqrt((p.posx - (pos.posx - xMax))*(p.posx - (pos.posx - xMax)) + (p.posy - pos.posy)*(p.posy - pos.posy)); //echo
	distancia[5] = sqrt((p.posx - (pos.posx + xMax))*(p.posx - (pos.posx + xMax)) + (p.posy - pos.posy)*(p.posy - pos.posy)); //echo
	distancia[2] = sqrt((p.posx - pos.posx)*(p.posx - pos.posx) + (p.posy - (pos.posy - yMax))*(p.posy - (pos.posy - yMax))); // echo
	distancia[7] = sqrt((p.posx - (pos.posx - xMax))*(p.posx - (pos.posx - xMax)) + (p.posy - (pos.posy - yMax))*(p.posy - (pos.posy - yMax))); //echo
	distancia[7] = sqrt((p.posx - (pos.posx + xMax))*(p.posx - (pos.posx + xMax)) + (p.posy - (pos.posy - yMax))*(p.posy - (pos.posy - yMax))); //echo
	int smallest = distancia[0];
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


double deg2rad(double angulo_deg)
{
	const double pi = atan(1) * 4;
	return ((angulo_deg*pi) / 180.0);
}