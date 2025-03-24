#ifndef _FIELD_H_
#define _FIELD_H_

#define FIELD_SIZE 36

extern const int FIELD_MAX_WATER;


typedef enum {
	PLANT_NONE,
	PLANT_CARROT,
	PLANT_TURNIP,
	PLANT_POTATO,
	PLANT_ONION,
} Plant;


typedef struct {
	int water;
	int time_left;
	Plant plant;
} FieldTile;


typedef struct {
	int x, y, w, h;
	FieldTile tiles[FIELD_SIZE];
	Plant target;
} Field;


typedef struct {
	Plant plant;
	int amount;
} HarvestResult;


FieldTile* field_find_tile(Field* field, int x, int y);
Field field_create(int x, int y, int w, int h, Plant target);
void field_update(Field* field);
void field_set_plant(Field* field, Plant target);
int field_get_x(Field* field, int index);
int field_get_y(Field* field, int index);

void field_plant(Field* field, int x, int y, Plant plant);
void field_water(Field* field, int x, int y);
HarvestResult field_harvest(Field* field, int x, int y);


#endif // _FIELD_H_
