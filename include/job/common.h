#ifndef _JOB_COMMON_H_
#define _JOB_COMMON_H_


#include "gamestate.h"
#include "job/job.h"


#define FREE_CONTEXT_FN(ContextStruct) \
void ContextStruct##_free(void* context) { \
	ContextStruct *_context = context; \
	free(_context); \
}


typedef struct {
	int x, y;
	Actor* actor;
} MoveJobContext;


typedef struct {
	unsigned short time_left;
} IdleJobContext;


void MoveJobContext_free(void* context);
void IdleJobContext_free(void* context);

MoveJobContext* move_job_context_create(Actor* actor, int x, int y);

void move_job_queue(JobQueue* queue, Actor* actor, int x, int y);
Job idle_job_create(int time);
Job wander_job_create(Actor* actor, int origin_x, int origin_y, int dx, int dy);

#endif // _JOB_COMMON_H_
