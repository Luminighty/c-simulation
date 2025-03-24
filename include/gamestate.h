#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "field.h"
#include "job/job.h"
#include <stdbool.h>


#define BERRY_SIZE 10
#define FIELD_AMOUNT 4
#define ACTOR_SIZE 2

typedef struct {
	int x, y;
	int tick;
	int wither;
	short berry_c;
} BerryBush;


typedef struct {
	int x, y;
	JobQueue job_queue;
} Actor;


typedef struct {
	Job* jobs[FIELD_AMOUNT];
	void* taken[FIELD_AMOUNT];
} JobBoard;


typedef struct {
	Actor actors[ACTOR_SIZE];
	Field fields[FIELD_AMOUNT];
	BerryBush berries[BERRY_SIZE];
	JobBoard job_board;
	int carrots;
	int turnips;
	int potatoes;
	int onions;
} GameState;


GameState gamestate_create();
void gamestate_destroy(GameState* gamestate);


#endif // _GAMESTATE_H_
