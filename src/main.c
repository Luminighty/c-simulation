#include <SDL2/SDL.h>
#include "config.h"
#include "app.h"
#include "gamestate.h"
#include "poll_events.h"
#include "render.h"
#include "terminal.h"
#include "update.h"


int main() {
	App app = app_create();
	GameState gamestate = gamestate_create();
	Terminal terminal = terminal_create(app.renderer, "assets/ascii.png", CHAR_WIDTH, CHAR_HEIGHT, CHAR_SCALE);

	init(&gamestate);
	while (!app.quit) {
		poll_events(&app);
		update(&gamestate);
		render(&terminal, &gamestate);

		terminal_render(app.renderer, &terminal);
		SDL_RenderPresent(app.renderer);
		SDL_Delay(200);
	}

	terminal_destroy(&terminal);
	app_destroy(&app);
	return 0;
}

