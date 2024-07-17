#include "gamestate.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


GameState gamestate_create() {
	GameState gamestate;
	gamestate.player.x = 15;
	gamestate.player.y = 15;
	gamestate.player.target_x = gamestate.player.x;
	gamestate.player.target_y = gamestate.player.y;
	gamestate.player.berry_count = 5;
	gamestate.player.hunger = 0;

	srand(time(NULL));
	for (int i = 0; i < BERRY_SIZE; i++) {
		int x = rand() % MAP_WIDTH;
		int y = rand() % MAP_HEIGHT;
		gamestate.berries[i].x = x;
		gamestate.berries[i].y = y;
		gamestate.berries[i].berry_c = rand() % 3;
		gamestate.berries[i].tick = rand() % 5;
	}

	return gamestate;
}

