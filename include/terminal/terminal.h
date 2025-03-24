#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <SDL2/SDL.h>
#include "terminal/color.h"

#define TERMINAL_WIDTH 40
#define TERMINAL_HEIGHT 40
#define TERMINAL_SIZE TERMINAL_WIDTH * TERMINAL_HEIGHT
#define CHARMAP_WIDTH 16
#define CHARMAP_HEIGHT 16

typedef struct {
	unsigned char c;
	Color fg;
	Color bg;
} Glyph;


typedef struct {
	int w, h;
	Glyph glyphs[TERMINAL_SIZE];
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Texture* texture;
} Terminal;


Terminal terminal_create(SDL_Renderer* renderer, const char* ascii_file, int char_width, int char_height, int scale);
Glyph glyph_create(unsigned char c, Color fg, Color bg);
void terminal_render(SDL_Renderer* renderer, Terminal* terminal);
void terminal_clear(Terminal* terminal);
void terminal_put(Terminal* terminal, int x, int y, unsigned char c, Color fg, Color bg);
void terminal_destroy(Terminal* terminal);


#endif // _TERMINAL_H_
