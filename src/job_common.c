#include "job_common.h"
#include "gamestate.h"
#include "job.h"
#include "log.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>


static void free_move_context(void* context) {
	MoveJobContext* _context = context;
	free(_context);
}

MoveJobContext* move_job_context_create(int x, int y) {
	MoveJobContext* context = (MoveJobContext *)malloc(sizeof(MoveJobContext));
	context->x = x;
	context->y = y;
	return context;
}


void move_job_execute(JobQueue *queue, void* gamestate, void* context) {
	GameState* state = gamestate;
	MoveJobContext* job = context;
	int dx = job->x - state->player.x;
	int dy = job->y - state->player.y;
	int dist = abs(dx) + abs(dy);
	char buffer[128];
	sprintf(buffer, "move %d", dist);
	log_message("move");
	if (abs(dx) + abs(dy) <= 1) {
		job_pop(queue);
		return;
	}
	if (abs(dx) > abs(dy)) {
		state->player.x += sign(dx);
	} else {
		state->player.y += sign(dy);
	}
}


void move_job_queue(JobQueue *queue, int x, int y) {
	job_push(queue, job_create(1, move_job_context_create(x, y), move_job_execute, free_move_context));
}
