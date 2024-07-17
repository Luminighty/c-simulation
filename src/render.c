#include "render.h"
#include "SDL_stdinc.h"
#include "color.h"
#include "gamestate.h"
#include "terminal.h"


static Color PURPLE = { 120, 0, 255 };


static void render_str(Terminal* terminal, int x, int y, char* str, Color fg, Color bg) {
	int i = 0;
	while (str[i]) {
		terminal_put(terminal, x, y, str[i], fg, bg);
		x++;
		i++;
	}
}


static void render_num(Terminal* terminal, int x, int y, int num, Color fg, Color bg) {
	char text[32];
	SDL_itoa(num, text, 10);
	render_str(terminal, x, y, text, fg, bg);
}


void render(Terminal *terminal, GameState *gamestate) {
	terminal_clear(terminal);

	for (int i = 0; i < TERMINAL_SIZE; i++)
		terminal_put(
			terminal, 
			i % terminal->w,
			i / terminal->w,
			0xFA,
			DARK_GREEN, BLACK
		);

	for (int i = 0; i < BERRY_SIZE; i++)
		terminal_put(
			terminal,
			gamestate->berries[i].x,
			gamestate->berries[i].y,
			0xB2,
			GREEN,
			gamestate->berries[i].berry_c > 0 ? PURPLE : BLACK
		);

	
	terminal_put(
		terminal, 
		gamestate->player.x,
		gamestate->player.y,
		0x02, WHITE, BLACK
	);

	render_str(terminal, 0, 0, "berries: ", WHITE, BLACK);
	render_num(terminal, 9, 0, gamestate->player.berry_count, WHITE, BLACK);
}

