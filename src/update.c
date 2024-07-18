#include "update.h"
#include "config.h"
#include "field.h"
#include "gamestate.h"
#include "job.h"
#include "job_field.h"
#include <stdlib.h>


static int distance(int from_x, int from_y, int to_x, int to_y) {
	return abs(from_x - to_x) + abs(from_y - to_y);
}

static void find_bush(GameState* gamestate) {
	int min = -1;
	int min_dist = 0;
	int max_berries = 0;
	for (int i = 0; i < BERRY_SIZE; i++) {
		if (gamestate->berries[i].berry_c < 1)
			continue;
		int dist = distance(
			gamestate->player.x, gamestate->player.y,
			gamestate->berries[i].x, gamestate->berries[i].y
		);
		int berries = gamestate->berries[i].berry_c;
		if (min == -1 || dist < min_dist - max_berries) {
			min = i;
			min_dist = dist;
			max_berries = berries;
		}
	}
	if (min == -1)
		return;
	gamestate->player.target_x = gamestate->berries[min].x;
	gamestate->player.target_y = gamestate->berries[min].y;
}


static void try_forage(GameState* gamestate) {
	for (int i = 0; i < BERRY_SIZE; i++) {
		int dist = distance(gamestate->berries[i].x, gamestate->berries[i].y, gamestate->player.x, gamestate->player.y);
		if (dist > 1)
			continue;
		gamestate->player.berry_count += gamestate->berries[i].berry_c;
		gamestate->berries[i].berry_c = 0;
	}
}


static void step_actor(Actor* actor) {
	int dx = actor->target_x - actor->x;
	int dy = actor->target_y - actor->y;
	if (abs(dx) > abs(dy)) {
		actor->x += dx > 0 ? 1 : -1;
	} else {
		actor->y += dy > 0 ? 1 : -1;
	}
	
	actor->hunger += rand() % 2;
	if (actor->hunger > 4) {
		actor->hunger = 0;
		actor->berry_count--;
	}
}


static void tick_bush(BerryBush* bush) {
	if ((rand() % 100) < 5) {
		bush->wither++;
		if (bush->wither >= 20)
			bush->berry_c = 0;
	}
	if (rand() % 100 > 20)
		return;
	if (bush->wither > 20) {
		bush->x = rand() % MAP_WIDTH;
		bush->y = rand() % MAP_HEIGHT;
		bush->berry_c = 0;
		bush->tick = 0;
		bush->wither = 0;
	}
	bush->tick++;
	if (bush->tick > 10) {
		bush->berry_c++;
		bush->tick = 0;
	}
}

void init(GameState* gamestate) {
	find_bush(gamestate);
}

void update(GameState* gamestate) {
	if (job_is_empty(&gamestate->job_queue)) {
		Job job;
		field_job_query(&gamestate->field, &job);

		if (job.context)
			job_push(&gamestate->job_queue, job);
		return;
	}
	job_execute(&gamestate->job_queue, gamestate);

	field_update(&gamestate->field);
	

	/*
	int target_distance = distance(gamestate->player.x, gamestate->player.y, gamestate->player.target_x, gamestate->player.target_y);
	if (target_distance < 2) {
		try_forage(gamestate);
		find_bush(gamestate);
	}

	step_actor(&gamestate->player);
	for (int i = 0; i < BERRY_SIZE; i++)
		tick_bush(&gamestate->berries[i]);
	*/
}

