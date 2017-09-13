#pragma once

struct position
{
	double posx;
	double posy;
};

class Bird
{
public:
	Bird(void);
	void SetGlobalXYMax(unsigned int xMax, unsigned int yMax);
	void calculateNewDir(Bird * birds, unsigned int birdCount);
	void move(void); // modified
	void incrementEyesight(void);
	bool decrementEyesight(void);
	void incrementSpeed(void);
	bool decrementSpeed(void);
	void incrementMaxRandomJiggle(void);
	bool decrementMaxRandomJiggle(void);
	position getPos(void);
	double getDir(void);
	double getEyesight(void);
	double getMaxRandomJiggle(void);
	double getSpeed(void);
	void initRandom(unsigned int udEyesight,unsigned int udSpeed);

private:
	position p;
	double currentDir;
	double newDir;
	unsigned int eyesight;
	unsigned int maxRandomJiggle;
	unsigned int speed;
	static unsigned int xMax;
	static unsigned int yMax;
	bool isBirdInSight(Bird * bird);
	double deg2rad(double angulo_deg);
};

