#include "color.h"


const Color RED = { 255, 0, 0 };
const Color GREEN = { 0, 255, 0 };
const Color DARK_GREEN = { 0, 155, 0 };
const Color BLUE = { 0, 0, 255 };

const Color WHITE = { 255, 255, 255 };
const Color BLACK = { 0, 0, 0, };

Color rgb(unsigned char r, unsigned char g, unsigned char b) {
	Color color = { r, g, b };
	return color;
}
