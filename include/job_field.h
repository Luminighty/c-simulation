#ifndef _JOB_FIELD_H_
#define _JOB_FIELD_H_

#include "field.h"
#include "job.h"


typedef struct {
	Field* field;
} FieldJobContext;


void field_job_query(Field* field, Job* job);
FieldJobContext* field_job_context_create(Field* field);
void field_job_water(JobQueue *queue, void* gamestate, void* context);

#define JOB_FIELD_WATER(field) job_create(20, field_job_context_create(field), field_job_water, free_context)

#endif // _JOB_FIELD_H_
