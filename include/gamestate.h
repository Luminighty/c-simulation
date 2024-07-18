#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "field.h"
#include "job.h"
#define BERRY_SIZE 10

typedef struct {
	int x, y;
	int tick;
	int wither;
	short berry_c;
} BerryBush;


typedef struct {
	int x, y;
	int target_x, target_y;
	int berry_count;
	int hunger;
} Actor;


typedef struct {
	Actor player;
	JobQueue job_queue;
	Field field;
	BerryBush berries[BERRY_SIZE];
} GameState;


GameState gamestate_create();
void gamestate_destroy(GameState* gamestate);

#endif // _GAMESTATE_H_
