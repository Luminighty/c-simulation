#include "poll_events.h"
#include "SDL_events.h"
#include <stdbool.h>


void poll_events(App* app) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			app->quit = 1;
			return;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				app->quit = 1;
			break;
		default:
			break;
		}
	}
}
