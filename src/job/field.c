#include "job/field.h"
#include "field.h"
#include "gamestate.h"
#include "job/job.h"
#include "job/common.h"
#include "math.h"
#include <stdlib.h>

#define JOB_FIELD_CREATE(priority, field, execute) job_create(priority, field_job_context_create(field), execute, free_context)


static int find_harvestable_field(Field* field) {
	for (int i = 0; i < field->w * field->h; i++)
		if (field->tiles[i].time_left <= 0 && field->tiles[i].plant != PLANT_NONE)
			return i;
	return -1;
}


static int min_water(Field* field) {
	int min = 0;
	for (int i = 1; i < field->w * field->h; i++)
		if (field->tiles[i].water < field->tiles[min].water)
			min = i;
	return min;
}


static int find_empty_field(Field* field) {
	for (int i = 0; i < field->w * field->h; i++)
		if (field->tiles[i].plant == PLANT_NONE)
			return i;
	return -1;
}


FieldJobContext* field_job_context_create(Field* field) {
	FieldJobContext* context = (FieldJobContext*)malloc(sizeof(FieldJobContext));
	context->field = field;
	context->actor = 0;
	return context;
}


static void free_context(void* context) {
	FieldJobContext* _context = context;
	free(_context);
}


void field_job_harvest(JobQueue* queue, void* gamestate, void* context) {
	GameState* state = gamestate;
	FieldJobContext* job = context;
	int index = find_harvestable_field(job->field);
	if (index == -1) {
		job_pop(queue);
		return;
	}
	int target_x = field_get_x(job->field, index);
	int target_y = field_get_y(job->field, index);
	if (distance(job->actor->x, job->actor->y, target_x, target_y) > 1) {
		move_job_queue(queue, job->actor, target_x, target_y);
		return;
	}

	HarvestResult result = field_harvest(job->field, target_x, target_y);
	switch (result.plant) {
	case PLANT_NONE:
		break;
	case PLANT_CARROT:
		state->carrots += result.amount;
		break;
	case PLANT_TURNIP:
		state->turnips += result.amount;
		break;
	case PLANT_POTATO:
		state->potatoes += result.amount;
		break;
	case PLANT_ONION:
		state->onions += result.amount;
		break;
	}
	job->actor = 0;
	job_close(job_head(queue));
	job_pop(queue);
}


void field_job_plant(JobQueue* queue, void* gamestate, void* context) {
	GameState* state = gamestate;
	FieldJobContext* job = context;
	int index = find_empty_field(job->field);
	if (index == -1) {
		job_pop(queue);
		return;
	}
	int target_x = field_get_x(job->field, index);
	int target_y = field_get_y(job->field, index);
	if (distance(job->actor->x, job->actor->y, target_x, target_y) > 1) {
		move_job_queue(queue, job->actor, target_x, target_y);
		return;
	}

	field_plant(job->field, target_x, target_y, job->field->target);
	job->actor = 0;
	job_close(job_head(queue));
	job_pop(queue);
}


void field_job_water(JobQueue *queue, void* gamestate, void* context) {
	GameState* state = gamestate;
	FieldJobContext* job = context;

	int index = min_water(job->field);
	int target_x = field_get_x(job->field, index);
	int target_y = field_get_y(job->field, index);

	if (distance(job->actor->x, job->actor->y, target_x, target_y) > 1) {
		move_job_queue(queue, job->actor, target_x, target_y);
		return;
	}
	
	field_water(job->field, target_x, target_y);
	job->actor = 0;
	job_close(job_head(queue));
	job_pop(queue);
}


void field_job_query(Field *field, Job* job) {
	int min_water_index = min_water(field);
	if (field->tiles[min_water_index].water < 80 && job_compare(job, 30)) {
		job_update(job, JOB_FIELD_CREATE(30, field, field_job_water));
		return;
	}
	int harvestable = find_harvestable_field(field);
	if (harvestable != -1 && job_compare(job, 25)) {
		job_update(job, JOB_FIELD_CREATE(25, field, field_job_harvest));
		return;
	}
	int empty_field = find_empty_field(field);
	if (empty_field != -1 && job_compare(job, 20)) {
		job_update(job, JOB_FIELD_CREATE(20, field, field_job_plant));
		return;
	}
}

