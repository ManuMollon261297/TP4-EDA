#include "controller.h"

const float FPS = 30.0;

controller::controller(){
	event_queue =  nullptr;
	timer = nullptr;
	display = nullptr;
}
		

int controller::justinit() {

	if (!al_install_keyboard()) {
		return -1;
	}

	event_queue = al_create_event_queue();

	if (event_queue == nullptr) {
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		return -1;
	}
	else {
		al_start_timer(timer);
	}
	event_queue = al_create_event_queue();
	if (event_queue == nullptr) {
		return -1;
	}

	key_pressed = "INIT";
	toggle_key = 0;

	// Los siguientes son valores de prueba

	eyesight = 0;
	randomjiggle = 0;
	speed = 0;
	maxspeed = 20;
	maxeyesight = 10;
	maxrandomjiggle = 10;
	return 0;
}

int controller::register_events() {
	if (display != nullptr) {
		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
	}
	else {
		return -1; // display wasn't shared with controller
				   // so it doesn't make sense to even register any kind of event
	}

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
	if (evs.type == ALLEGRO_EVENT_TIMER) {
	
	}
	else if (evs.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (toggle_key == 0) {
			key_pressed = al_keycode_to_name(evs.keyboard.keycode);
			toggle_key = 1;
		}		
	}
	else if (evs.type == ALLEGRO_EVENT_KEY_UP) {
		if (toggle_key == 1) {
			toggle_key = 0;
			key_pressed = "RESET";
		}
	}
	if (!key_pressed.compare("KEY62")) { // +
		if (speed < maxspeed) {
			speed++;
		}
	}
	if (!key_pressed.compare("KEY61")) { // - 
		if (speed > 0) {
			speed--;
		}
	}
	if (!key_pressed.compare("E")) {
		if (randomjiggle < maxrandomjiggle) {
			randomjiggle++;
		}
	}
	if (!key_pressed.compare("D")) {
		if (randomjiggle > 0) {
			randomjiggle--;
		}
	}
	if (!key_pressed.compare("R")) {
		if (eyesight < maxeyesight) {
			eyesight++;
		}
	}
	if (!key_pressed.compare("F")) {
		if (eyesight > 0) {
			eyesight--;
		}
	
	}
}