#include "controller.h"

const float FPS = 60.0;

controller::controller(unsigned int toggle_key_, unsigned int timer_c_, std::string key_pressed_) {
	event_queue =  nullptr;
	timer = nullptr;
	display = nullptr;
	toggle_key = toggle_key_;
	timer_c = timer_c_;
	key_pressed = key_pressed_;
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
	if (timer == nullptr) {
		return -1;
	}
	else {
		al_start_timer(timer);
	}

	
	timerc_max = 5; // esta variable es de ajuste fino de la actualizacion 
	// de teclas


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
	int ans = 0;
	if (display != nullptr) {
		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
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
	if (evs.type == ALLEGRO_EVENT_TIMER) {
		
		if (timer_c < timerc_max) {
			timer_c++;
		}
		else {
			timer_c = 0;
		}
	}
	// deberia poner que cada cierto tiempo se pueda incrementar 

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

	if (timer_c == timerc_max) {
		if (!key_pressed.compare("KEY62")) { // +
		/*
			for (int i = 0; i < birdcount; i++) {
				if (bird[i].speed < bird.maxspeed) {
					bird[i].incrementSpeed();
				}
			
			}
		*/
			if (speed < maxspeed) {
				speed++;
			}
		}
		if (!key_pressed.compare("KEY61")) { // - 
			
		 /*
			for (int i = 0; i < birdcount; i++) {
				if (bird[i].speed > 0 ) {
					bird[i].decrementSpeed;
				}	
			}
		*/
			
			if (speed > 0) {
				speed--;
			}
		}
		if (!key_pressed.compare("E")) {
			/*
			for (int i = 0; i < birdcount; i++) {
			if(bird[i].maxRandomJiggle < 10 )
			bird[i].incrementmaxRandomJiggle;
			}
			*/


			if (randomjiggle < maxrandomjiggle) {
				randomjiggle++;
			}
		}
		if (!key_pressed.compare("D")) {
			/*
			for (int i = 0; i < birdcount; i++) {
				if(bird[i].maxRandomJiggle>0){
					bird[i].decrementmaxRandomJiggle;
				}
			}
			*/
			
			if (randomjiggle > 0) {
				randomjiggle--;
			}
		}

		if (!key_pressed.compare("R")) {
			/*
			for (int i = 0; i < birdcount; i++) {
				if(bird[i].eyesight<eyesightMax){
					bird[i].incrementEyesight();
				}
			}
			*/

			if (eyesight < maxeyesight) {
				eyesight++;
			}
		}
		if (!key_pressed.compare("F")) {

			/*
			for (int i = 0; i < birdcount; i++) {
				if(bird[i].eyesight>0){
					bird[i].decrementEyesight();
				}
			}
			*/
			if (eyesight > 0) {
				eyesight--;
			}
		}
	}

	
}
void controller::destroy_controller_utils(void) {
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}
