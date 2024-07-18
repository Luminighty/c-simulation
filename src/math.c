#include "math.h"
#include <stdlib.h>


int distance(int from_x, int from_y, int to_x, int to_y) {
	return abs(from_x - to_x) + abs(from_y - to_y);
}


int sign(int value) {
	if (value == 0)
		return 0;
	return value > 0 ? 1 : -1;
}

