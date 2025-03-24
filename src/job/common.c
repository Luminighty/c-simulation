#include "job/common.h"
#include "gamestate.h"
#include "job/job.h"
#include "math.h"
#include <stdlib.h>


FREE_CONTEXT_FN(IdleJobContext);
FREE_CONTEXT_FN(MoveJobContext);


void move_job_execute(JobQueue *queue, void* gamestate, void* context) {
	GameState* state = gamestate;
	MoveJobContext* job = context;
	int dx = job->x - job->actor->x;
	int dy = job->y - job->actor->y;
	int dist = abs(dx) + abs(dy);
	if (abs(dx) + abs(dy) <= 1) {
		job_pop(queue);
		return;
	}
	if (abs(dx) > abs(dy)) {
		job->actor->x += sign(dx);
	} else {
		job->actor->y += sign(dy);
	}
}


void idle_job_execute(JobQueue* queue, void* gamestate, void* context) {
	IdleJobContext* job = context;
	if (job->time_left > 0) {
		job->time_left--;
		return;
	}
	job_pop(queue);
}


Job idle_job_create(int time) {
	IdleJobContext* context = malloc(sizeof(IdleJobContext));
	context->time_left = time;
	return job_create(0, context, idle_job_execute, IdleJobContext_free);
}


Job move_job_create(Actor* actor, int x, int y) {
	MoveJobContext* context = malloc(sizeof(MoveJobContext));
	context->x = x;
	context->y = y;
	context->actor = actor;
	return job_create(
		1, 
		context,
		move_job_execute, 
		MoveJobContext_free
	);
}


void move_job_queue(JobQueue *queue, Actor* actor, int x, int y) {
	job_push(
		queue, 
		move_job_create(actor, x, y)
	);
}


Job wander_job_create(Actor* actor, int origin_x, int origin_y, int dx, int dy) {
	int target_x = origin_x + rand() % (dx * 2) - dx;
	int target_y = origin_y + rand() % (dy * 2) - dy;

	return move_job_create(actor, target_x, target_y);
}

