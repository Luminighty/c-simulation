#include "job.h"
#include "log.h"


JobQueue jobqueue_create() {
	JobQueue queue;
	queue.length = 0;
	return queue;
}


Job job_create(
	int priority, 
	void *context, 
	void (*execute)(JobQueue*, void*, void*),
	void (*_free)(void*)
) {
	Job job;
	job.priority = priority;
	job.context = context;
	job.execute = execute;
	job.free = _free;
	return job;
}


void job_destroy(Job* job) {
	if (job->context)
		job->free(job->context);
}


void job_update(Job *job, Job other) {
	if (job)
		job_destroy(job);
	job->context = other.context;
	job->free = other.free;
	job->priority = other.priority;
	job->execute = other.execute;
}

void job_pop(JobQueue *queue) {
	if (queue->length > 0) {
		queue->length--;
		job_destroy(&queue->queue[queue->length]);
	}
}


void job_push(JobQueue *queue, Job job) {
	if (queue->length >= JOB_QUEUE_SIZE) {
		log_warn("Job queue full!");
		job_clear_queue(queue);
		return;
	}
	int index = queue->length;
	queue->queue[index] = job;
	queue->length++;
}


bool job_is_empty(JobQueue *queue) {
	return queue->length == 0;
}


static Job* job_head(JobQueue* queue) {
	if (queue->length == 0)
		return 0;
	return &queue->queue[queue->length - 1];
}

void job_execute(JobQueue *queue, void *world_context) {
	Job* head = job_head(queue);
	head->execute(
		queue,
		world_context,
		head->context
	);
}


void job_clear_queue(JobQueue *queue) {
	while(!job_is_empty(queue))
		job_pop(queue);
}
