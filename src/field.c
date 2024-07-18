#include "field.h"
#include "log.h"
#include <stdlib.h>


Field field_create(int x, int y, int w, int h, Plant target) {
	Field field;
	field.x = x;
	field.y = y;
	field.w = w;
	field.h = h;
	field.target = target;

	for (int i = 0; i < w * h; i++) {
		field.tiles[i].water = 0;
		field.tiles[i].plant = PLANT_NONE;
		field.tiles[i].time_left = 0;
	}
	return field;
}


void field_set_plant(Field *field, Plant target) {
	field->target = target;
}


void field_plant(Field *field, int x, int y, Plant plant) {
	FieldTile* tile = field_find_tile(field, x, y);
	if (!tile)
		return;
}


void field_water(Field *field, int x, int y) {
	FieldTile* tile = field_find_tile(field, x, y);
	if (!tile)
		return;
	tile->water = FIELD_MAX_WATER;
}


void field_update(Field *field) {
	for (int i = 0; i < field->w * field->h; i++) {
		if (field->tiles[i].water > 0)
			field->tiles[i].water -= rand() % 2;
		if (field->tiles[i].plant == PLANT_NONE)
			continue;
		field->tiles[i].time_left -= rand() % 2;

		if (field->tiles[i].water < 0) {
			field->tiles[i].plant = PLANT_NONE;
			field->tiles[i].time_left = 0;
		}
	}
}


int field_get_x(Field *field, int index) {
	return field->x + index % field->w;
}


int field_get_y(Field *field, int index) {
	return field->y + index / field->w;
}


FieldTile* field_find_tile(Field* field, int x, int y) {
	x -= field->x;
	y -= field->y;
	int i = x + y * field->w;
	if (i >= field->w * field->h || i < 0)
		return 0;
	return &field->tiles[i];
}


HarvestResult field_harvest(Field *field, int x, int y) {
	HarvestResult result;
	FieldTile* tile = field_find_tile(field, x, y);
	if (!tile)
		return result;
	
	result.plant = tile->plant;
	result.amount = rand() % 5 + 1;
	if (tile->time_left > 0) {
		result.amount = 0;
		result.plant = PLANT_NONE;
	}
	tile->plant = PLANT_NONE;
	return result;
}

