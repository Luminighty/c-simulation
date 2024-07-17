#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>
#include <stdbool.h>


typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool quit;
} App;


App app_create();
void app_destroy(App* app);

#endif // _APP_H_
