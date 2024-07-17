#include "app.h"
#include "SDL_rect.h"
#include "SDL_video.h"
#include "config.h"

static SDL_HitTestResult titlebar_callback(SDL_Window* win, const SDL_Point* area, void* data) {
	if (area->y < 32)
		return SDL_HITTEST_DRAGGABLE;
	return SDL_HITTEST_NORMAL;
}

App app_create() {
	App app;

	SDL_Init(SDL_INIT_VIDEO);

	app.window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_BORDERLESS
	);

	SDL_SetWindowHitTest(app.window, titlebar_callback, NULL);

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	app.quit = false;

	return app;
}


void app_destroy(App *app) {
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
}

