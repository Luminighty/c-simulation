#include <SDL2/SDL.h>
#include "config.h"
#include "app.h"
#include "gamestate.h"
#include "log.h"
#include "poll_events.h"
#include "render.h"
#include "terminal.h"
#include "update.h"


void log_test() {
	log_message("log_message");
	log_error("log_error");
	log_warn("log_warn");
	log_debug("log_debug");
}

int main() {
	logger_create(LOG_LEVEL_DEBUG);
	App app = app_create();
	GameState gamestate = gamestate_create();
	Terminal terminal = terminal_create(app.renderer, "assets/ascii.png", CHAR_WIDTH, CHAR_HEIGHT, CHAR_SCALE);

	log_test();
	init(&gamestate);
	while (!app.quit) {
		poll_events(&app);
		update(&gamestate);
		render(&terminal, &gamestate);

		terminal_render(app.renderer, &terminal);
		SDL_RenderPresent(app.renderer);
		SDL_Delay(200);

		logger_clear(5000);
	}

	terminal_destroy(&terminal);
	app_destroy(&app);
	logger_destroy();
	return 0;
}

