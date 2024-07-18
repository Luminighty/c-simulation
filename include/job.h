#ifndef _JOB_H_
#define _JOB_H_


#include <stdbool.h>
#define JOB_QUEUE_SIZE 32


typedef struct JobQueue JobQueue;


typedef struct {
	int priority;
	void* context;
	void (*free)(void*);
	void (*execute)(JobQueue*, void*, void*);
} Job;


struct JobQueue {
	int length;
	Job queue[JOB_QUEUE_SIZE];
};


JobQueue jobqueue_create();
Job job_create(int priority, void *context, void (*execute)(JobQueue*, void*, void*), void (*free)(void*));
void job_update(Job* job, Job other);
void job_pop(JobQueue* queue);
void job_push(JobQueue* queue, Job job);
bool job_is_empty(JobQueue* queue);
void job_clear_queue(JobQueue* queue);
void job_execute(JobQueue* queue, void* world_context);


extern const Job NO_JOB;

#endif // _JOB_H_
