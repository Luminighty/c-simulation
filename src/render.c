#include "render.h"
#include "SDL_stdinc.h"
#include "terminal/color.h"
#include "field.h"
#include "gamestate.h"
#include "log.h"
#include "terminal/terminal.h"


static Color PURPLE = { 120, 0, 255 };


static void render_str(Terminal* terminal, int x, int y, const char* str, Color fg, Color bg) {
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


static Color log_color(LogMessageLevel level) {
	switch (level) {
		case LOG_LEVEL_MESSAGE:
			return WHITE;
		case LOG_LEVEL_ERROR:
			return RED;
		case LOG_LEVEL_WARN:
			return YELLOW;
		case LOG_LEVEL_DEBUG:
			return TEAL;
	}
}


static void print_logs(Terminal* terminal) {
	for (int i = 0; i < 10; i++) {
		Log* log = logger_get(i);
		if (!log)
			return;
		int y = terminal->h - i - 1;
		render_str(terminal, 0, y, log->message, log_color(log->level), BLACK);
	}
}


static void render_field_tile(Terminal* terminal, FieldTile* tile, int x, int y) {
	Color bg = tile->water > 50 ? DARK_BLUE : BLACK;
	Color fg;
	unsigned char c;
	switch (tile->plant) {
	case PLANT_NONE:
		c = 0xF7;
		fg = BROWN;
		break;
	case PLANT_CARROT:
		c = tile->time_left > 15 ? 0x2C : 0xF3;
		fg = tile->time_left > 5 ? GREEN : ORANGE;
		break;
	case PLANT_POTATO:
		c = tile->time_left > 15 ? 0x2C : 'o';
		fg = tile->time_left > 5 ? GREEN : LIGHT_BROWN;
		break;
	case PLANT_TURNIP:
		c = tile->time_left > 15 ? 0x2C : 0xF2;
		fg = tile->time_left > 5 ? GREEN : RED;
		break;
	case PLANT_ONION:
		c = tile->time_left > 15 ? 0x2C : 0xEB;
		fg = tile->time_left > 5 ? GREEN : LIGHT_BROWN;
		break;
	}
	terminal_put(terminal, x, y, c, fg, bg);
}


static void render_field(Terminal* terminal, Field* field) {
	for (int i = 0; i < field->w * field->h; i++) {
		int x = i % field->w;
		int y = i / field->w;
		render_field_tile(terminal, &field->tiles[i], x + field->x, y + field->y);
	}
}


void render(Terminal* terminal, GameState *gamestate) {
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
			gamestate->berries[i].wither >= 20 ? gray(100) : GREEN,
			gamestate->berries[i].berry_c > 0 ? PURPLE : BLACK
		);

	for (int i = 0; i < FIELD_AMOUNT; i++)
		render_field(terminal, &gamestate->fields[i]);

	for (int i = 0; i < ACTOR_SIZE; i++)
		terminal_put(
			terminal, 
			gamestate->actors[i].x,
			gamestate->actors[i].y,
			0x01 + i, WHITE, BLACK
		);

	render_str(terminal, 0, 0, "carrots:  ", WHITE, BLACK);
	render_str(terminal, 0, 1, "turnips:  ", WHITE, BLACK);
	render_str(terminal, 0, 2, "potatoes: ", WHITE, BLACK);
	render_str(terminal, 0, 3, "onions:  ", WHITE, BLACK);
	render_num(terminal, 10, 0, gamestate->carrots, WHITE, BLACK);
	render_num(terminal, 10, 1, gamestate->turnips, WHITE, BLACK);
	render_num(terminal, 10, 2, gamestate->potatoes, WHITE, BLACK);
	render_num(terminal, 10, 3, gamestate->onions, WHITE, BLACK);

	print_logs(terminal);
}

