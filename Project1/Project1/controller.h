#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <allegro5\allegro.h>
#include <iostream>
#include <string.h>
#include "Bird.h"


using namespace std;

class controller {
private:
	unsigned int toggle_key;
	unsigned int timer_c;
	unsigned int timerc_max;
	unsigned int birdcount;
	Bird * birds;

public:
	unsigned int maxrandomjigglelimit;
	unsigned int maxspeed;       
	unsigned int maxeyesight;   

	std::string key_pressed;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT evs;
	
	controller(unsigned int toggle_key_ = 0, unsigned int timer_c_ = 0, std::string key_pressed_ = "INIT", unsigned int maxrandomjigglelimit_ = 10, unsigned int maxspeed_ = 20);
	int control_init();
	int register_events();
	int isnotexit();
	void update_ctrl(void);
	void setBirdCount(unsigned int n);
	void setBirdPointer(Bird * p2bird);
	~controller(void);

};

#endif