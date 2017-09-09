#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <allegro5\allegro.h>
#include <iostream>
#include <string.h>

using namespace std;

class controller {
private:
//	bird* birds;
	unsigned int birdcount;

public:
	std::string key_pressed;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT evs;

	unsigned int eyesight;
	unsigned int randomjiggle;
	unsigned int maxrandomjiggle;
	unsigned int speed;
	unsigned int maxeyesight;
	unsigned int maxspeed;
	unsigned int toggle_key;

	controller();
	int justinit();
	int register_events();
	int isnotexit();
	void update_ctrl(void);
};

#endif