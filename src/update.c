#include "update.h"
#include "config.h"
#include "field.h"
#include "gamestate.h"
#include "job/job.h"
#include "job/common.h"
#include "job/field.h"
#include <stdlib.h>


static void tick_bush(BerryBush* bush) {
	if ((rand() % 100) < 5) {
		bush->wither++;
		if (bush->wither >= 20)
			bush->berry_c = 0;
	}
	if (rand() % 100 > 20)
		return;
	if (bush->wither > 20) {
		bush->x = rand() % MAP_WIDTH;
		bush->y = rand() % MAP_HEIGHT;
		bush->berry_c = 0;
		bush->tick = 0;
		bush->wither = 0;
	}
	bush->tick++;
	if (bush->tick > 10) {
		bush->berry_c++;
		bush->tick = 0;
	}
}

void init(GameState* gamestate) {
}

static Job noop_job(GameState* gamestate, Actor* actor)  {
	if (rand() % 100 > 50)
		return idle_job_create(rand() % 20 + 10);
	return wander_job_create(actor, 15, 15, 5, 5);
}


static void update_actor(GameState* gamestate, Actor* actor) {
	if (job_is_empty(&actor->job_queue)) {
		Job job = noop_job(gamestate, actor);
		for (int i = 0; i < FIELD_AMOUNT; i++) {
			Job* field_job = gamestate->job_board.jobs[i];
			if (
				field_job && 
				!field_job->is_closed && 
				!field_job->assignee &&
				field_job->context
			) {
				field_job->assignee = actor;
				job = field_job;
			}
		}

		if (job.context)
			job_push(&actor->job_queue, job);
	}
	if (!job_is_empty(&actor->job_queue))
		job_execute(&actor->job_queue, gamestate);
}


static void query_jobs(GameState* gamestate) {
	for (int i = 0; i < FIELD_AMOUNT; i++) {
		Job* job = gamestate->job_board.jobs[i];
		field_job_query(&gamestate->fields[i], job);
	}
}



void update(GameState* gamestate) {
	query_jobs(gamestate);
	for (int i = 0; i < FIELD_AMOUNT; i++)
		field_update(&gamestate->fields[i]);

	for (int i = 0; i < ACTOR_SIZE; i++)
		update_actor(gamestate, &gamestate->actors[i]);

	for (int i = 0; i < BERRY_SIZE; i++)
		tick_bush(&gamestate->berries[i]);
}

