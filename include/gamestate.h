#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#define BERRY_SIZE 10

typedef struct {
	int x, y;
	int tick;
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
	BerryBush berries[BERRY_SIZE];
} GameState;


GameState gamestate_create();

#endif // _GAMESTATE_H_
