#include "poll_events.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "log.h"
#include <stdbool.h>


static void on_key_up(App* app, SDL_KeyboardEvent* event) {
	if (event->keysym.sym == SDLK_ESCAPE)
		app->quit = 1;
	if (event->keysym.sym == SDLK_t) {
		app->always_on_top = !app->always_on_top;
		SDL_SetWindowAlwaysOnTop(app->window, app->always_on_top);
		if (app->always_on_top) {
			log_message("Always on top: ON");
		} else {
			log_message("Always on top: OFF");
		}
	}
	if (event->keysym.sym == SDLK_l) {
		log_message("log_message");
		log_error("log_error");
		log_warn("log_warn");
		log_debug("log_debug");
	}
}


void poll_events(App* app) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			app->quit = 1;
			return;
		case SDL_KEYUP:
			on_key_up(app, &event.key);
			break;
		default:
			break;
		}
	}
}
