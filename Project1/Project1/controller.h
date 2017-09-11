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
	
public:
	unsigned int maxrandomjigglelimit; /* estas no deben tenerun valor por default */
	unsigned int maxspeed;       //  ya que son las quen nos pasan con bird cada bird. 
	unsigned int maxeyesight;    // probablemente algunas de estas variables se tengan
	unsigned int birdcount;

	Bird * birds;

	std::string key_pressed;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT evs;
	
	controller(unsigned int toggle_key_ = 0, unsigned int timer_c_ = 0, std::string key_pressed_ = "INIT", unsigned int maxrandomjigglelimit_ = 10, unsigned int maxspeed_ = 20);
	int justinit();
	int register_events();
	int isnotexit();
	void update_ctrl(void);
	void destroy_controller_utils(void);

};

#endif