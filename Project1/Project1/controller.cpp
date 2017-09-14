#include "controller.h"

controller::controller(unsigned int toggle_key_ , std::string key_pressed_, unsigned int maxrandomjigglelimit_ , unsigned int maxspeed_, unsigned int maxeyesight_ ) {
	event_queue =  nullptr;

	display = nullptr;
	toggle_key = toggle_key_;
	key_pressed = key_pressed_;
	maxrandomjigglelimit = maxrandomjigglelimit_;
	maxspeed = maxspeed_;
	maxeyesight = maxeyesight_;
}
		

int controller::control_init() {

	if (!al_install_keyboard()) {
		return -1;
	}

	event_queue = al_create_event_queue();

	if (event_queue == nullptr) {
		return -1;
	}



	return 0;
}

int controller::register_events() {
	int ans = 0;
	if (display != nullptr) {
		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
	}
	else {
		ans = -1; // display wasn't shared with controller
				   // so it doesn't make sense to even register any kind of event
	}
	return ans;
}

int controller::isnotexit() {
	int ans = 1;
	if (al_get_next_event(event_queue, &evs)) {
				// if event comesup
		if (evs.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return 0;
		}
		else if (!strcmp(&key_pressed[0],"ESCAPE")) {
			return 0;
		}
	}
	return ans;
}

void controller::update_ctrl(void) {
	
	if (evs.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (toggle_key == 0) {
			key_pressed = al_keycode_to_name(evs.keyboard.keycode);
			toggle_key = 1;
		}		
	}
	else if (evs.type == ALLEGRO_EVENT_KEY_UP) {
		if (toggle_key == 1) {
			toggle_key = 0;
			process_key();
			key_pressed = "RESET";
		}
	}
}

//unsigned int maxrandomjigglelimit;
//unsigned int maxspeed;
//unsigned int maxeyesight;
//unsigned int birdcount;
void controller::setBirdCount(unsigned int n){
	birdcount = n;
}
void controller::setBirdPointer(Bird * p2bird) {
	if (p2bird != nullptr) {
		birds = p2bird;
	}
}
// display // set birds y setbirdcount


controller::~controller(void) {
	al_destroy_event_queue(event_queue);
}

void controller::process_key(void) {
	if (!key_pressed.compare("KEY62")) { //  KEY62 es '+'
		for (unsigned int i = 0; i < birdcount; i++) {
			if (birds[i].getSpeed() < maxspeed) {
				birds[i].incrementSpeed();
			}
		}
	}
	if (!key_pressed.compare("KEY61")) { // KEY 61 es '-' 
		for (unsigned int i = 0; i < birdcount; i++) {
			if (birds[i].getSpeed() > 0) {
				birds[i].decrementSpeed();
			}
		}
	}
	if (!key_pressed.compare("E")) {
		for (unsigned int i = 0; i < birdcount; i++) {
			if (birds[i].getMaxRandomJiggle() < maxrandomjigglelimit)
				birds[i].incrementMaxRandomJiggle();
		}
	}
	if (!key_pressed.compare("D")) {
		for (unsigned int i = 0; i < birdcount; i++) {
			if (birds[i].getMaxRandomJiggle()>0) {
				birds[i].decrementMaxRandomJiggle();
			}
		}
	}
	if (!key_pressed.compare("R")) {
		for (unsigned int i = 0; i < birdcount; i++) {
			if (birds[i].getEyesight() < maxeyesight) {
				birds[i].incrementEyesight();
			}
		}
	}
	if (!key_pressed.compare("F")) {
		for (unsigned int i = 0; i < birdcount; i++) {
			if ((birds[i].getEyesight()) > 0) {
				birds[i].decrementEyesight();
			}
		}
	}

}

bool controller::setDisplay(ALLEGRO_DISPLAY * display_) {
	display = display_;
	if (display == NULL)
	{
		return false;
	}
	return true;
}

ALLEGRO_DISPLAY * controller::getDisplay(void) {
	return display;
}

bool controller::setEventQueue(ALLEGRO_EVENT_QUEUE * eventQueue) {
	event_queue = eventQueue;
	return true;
}

ALLEGRO_EVENT_QUEUE * controller::getEventQueue(void) {
	return event_queue;
}

bool controller::setKeyPressed(string keyPressed) {
	key_pressed = keyPressed;
	return true;
}

string controller::getKeyPressed(void) {
	return key_pressed;
}