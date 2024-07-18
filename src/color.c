#include "color.h"


const Color RED = { 255, 0, 0 };
const Color GREEN = { 0, 255, 0 };
const Color DARK_GREEN = { 0, 155, 0 };
const Color BLUE = { 0, 0, 255 };
const Color DARK_BLUE = { 0, 0, 100 };
const Color YELLOW = { 255, 255, 0 };
const Color TEAL = { 0, 255, 255 };

const Color WHITE = { 255, 255, 255 };
const Color BLACK = { 0, 0, 0 };
const Color BROWN = { 100, 60, 50 };
const Color ORANGE = { 255, 77, 0 };


Color rgb(unsigned char r, unsigned char g, unsigned char b) {
	Color color = { r, g, b };
	return color;
}
