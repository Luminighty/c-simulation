#include "gamestate.h"
#include "config.h"
#include "field.h"
#include "job/job.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static Actor create_actor(int x, int y) {
	Actor actor;
	actor.x = x;
	actor.y = y;
	actor.job_queue = jobqueue_create();
	return actor;
}


GameState gamestate_create() {
	GameState gamestate;
	gamestate.actors[0] = create_actor(15, 15);
	gamestate.actors[1] = create_actor(18, 15);

	srand(time(NULL));
	for (int i = 0; i < BERRY_SIZE; i++) {
		int x = rand() % MAP_WIDTH;
		int y = rand() % MAP_HEIGHT;
		gamestate.berries[i].x = x;
		gamestate.berries[i].y = y;
		gamestate.berries[i].berry_c = rand() % 3;
		gamestate.berries[i].tick = rand() % 5;
		gamestate.berries[i].wither = rand() % 5;
	}

	gamestate.fields[0] = field_create(10, 10, 6, 4, PLANT_CARROT);
	gamestate.fields[1] = field_create(10, 16, 6, 4, PLANT_POTATO);
	gamestate.fields[2] = field_create(10, 22, 6, 4, PLANT_TURNIP);
	gamestate.fields[3] = field_create(10, 28, 6, 4, PLANT_ONION);

	for (int i = 0; i < FIELD_AMOUNT; i++) {
		gamestate.job_board.jobs[i] = 0;
		gamestate.job_board.taken[i] = 0;
	}

	gamestate.carrots = 0;
	gamestate.potatoes = 0;
	gamestate.turnips = 0;
	gamestate.onions = 0;

	return gamestate;
}


void gamestate_destroy(GameState *gamestate) {
	for (int i = 0; i < ACTOR_SIZE; i++)
		job_clear_queue(&gamestate->actors[i].job_queue);
}

