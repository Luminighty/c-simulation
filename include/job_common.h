#ifndef _JOB_COMMON_H_
#define _JOB_COMMON_H_


#include "job.h"
typedef struct {
	int x, y;
} MoveJobContext;


MoveJobContext* move_job_context_create(int x, int y);

void move_job_queue(JobQueue *queue, int x, int y);


#endif // _JOB_COMMON_H_
