#include "terminal.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_image.h"


static SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file) {
	SDL_Surface* surface = IMG_Load(file);
	if (surface == NULL) {
		printf("%s:%d Failed to load surface '%s'", __FILE__, __LINE__, file);
		exit(1);
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("%s:%d Failed to create texture from '%s'", __FILE__, __LINE__, file);
		exit(1);
	}

	SDL_FreeSurface(surface);

	return texture;
}


Terminal terminal_create(
	SDL_Renderer* renderer,
	const char* ascii_file, 
	int char_width, 
	int char_height, 
	int scale
) {
	Terminal terminal;
	terminal.h = TERMINAL_HEIGHT;
	terminal.w = TERMINAL_WIDTH;
	SDL_Rect src = { 0, 0, char_width, char_height };
	terminal.src = src;
	SDL_Rect dst = { 0, 0, char_width * scale, char_height * scale };
	terminal.dst = dst;
	terminal.texture = load_texture(renderer, ascii_file);
	terminal_clear(&terminal);
	return terminal;
}


void terminal_destroy(Terminal* terminal) {
	SDL_DestroyTexture(terminal->texture);
}


void terminal_put(Terminal *terminal, int x, int y, unsigned char c, Color fg, Color bg) {
	int i = x + y * terminal->w;
	if (i < 0 || i >= TERMINAL_SIZE)
		return;
	terminal->glyphs[i].c = c;
	terminal->glyphs[i].fg = fg;
	terminal->glyphs[i].bg = bg;
}


void terminal_render(SDL_Renderer *renderer, Terminal* terminal) {
	int size = terminal->w * terminal->h;
	for (int i = 0; i < size; i++) {
		int x = i % terminal->w;
		int y = i / terminal->w;
		Glyph* glyph = &terminal->glyphs[i];
		SDL_SetRenderDrawColor(renderer, glyph->bg.r, glyph->bg.g, glyph->bg.b, 255);
		terminal->dst.x = x * terminal->dst.w;
		terminal->dst.y = y * terminal->dst.h;
		SDL_RenderFillRect(renderer, &terminal->dst);

		SDL_SetTextureColorMod(terminal->texture, glyph->fg.r, glyph->fg.g, glyph->fg.b);

		terminal->src.x = (glyph->c % CHARMAP_WIDTH) * terminal->src.w;
		terminal->src.y = (glyph->c / CHARMAP_WIDTH) * terminal->src.w;
		SDL_RenderCopy(renderer, terminal->texture, &terminal->src, &terminal->dst);
	}
}


Glyph glyph_create(unsigned char c, Color fg, Color bg) {
	Glyph g = { c, fg, bg };
	return g;
}


void terminal_clear(Terminal *terminal) {
	int size = terminal->w * terminal->h;
	for (int i = 0; i < size; i++) {
		terminal->glyphs[i].c = ' ';
		terminal->glyphs[i].fg = BLACK;
		terminal->glyphs[i].bg = BLACK;
	}
}

