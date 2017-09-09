#pragma once

struct position
{
	double posx;
	double posy;
};

class Bird
{
public:
	Bird(unsigned int eyesight_ = 0, unsigned int maxRandomJiggle_ = 0, unsigned int speed_ = 5);
	void SetGlobalXYMax(unsigned int xMax, unsigned int yMax);
	void calculateNewDir(Bird * birds, unsigned int birdCount);
	void move(void);
	void incrementEyesight(void);
	void decrementEyesight(void);
	void incrementSpeed(void);
	void decrementSpeed(void);
	void incrementMaxRandomJiggle(void);
	void decrementMaxRandomJigggle(void);
	position getPos(void);
	double getDir(void);
	double getEyesight(void);
	double getMaxRandomJiggle(void);

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

