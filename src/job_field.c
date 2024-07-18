#include "job_field.h"
#include "field.h"
#include "gamestate.h"
#include "job.h"
#include "job_common.h"
#include "log.h"
#include "math.h"
#include <stdlib.h>

#define JOB_FIELD_WATER(field) job_create(20, field_job_context_create(field), field_job_water, free_context)


static int min_water(Field* field) {
	int min = 0;
	for (int i = 1; i < field->w * field->h; i++)
		if (field->tiles[i].water < field->tiles[min].water)
			min = i;
	return min;
}


FieldJobContext* field_job_context_create(Field* field) {
	FieldJobContext* context = (FieldJobContext*)malloc(sizeof(FieldJobContext));
	context->field = field;
	return context;
}


static void free_context(void* context) {
	FieldJobContext* _context = context;
	free(_context);
}


void field_job_water(JobQueue *queue, void* gamestate, void* context) {
	GameState* state = gamestate;
	FieldJobContext* job = context;

	int index = min_water(job->field);
	int target_x = field_get_x(job->field, index);
	int target_y = field_get_y(job->field, index);

	if (distance(state->player.x, state->player.y, target_x, target_y) > 1) {
		log_message("pushing move");
		move_job_queue(queue, target_x, target_y);
		return;
	}
	
	log_message("water");
	field_water(job->field, target_x, target_y);
	job_pop(queue);
}


void field_job_query(Field *field, Job* job) {
	int min_water_index = min_water(field);
	if (field->tiles[min_water_index].water < 15)
		job_update(job, JOB_FIELD_WATER(field));
}


