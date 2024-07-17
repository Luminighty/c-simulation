#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct {
	unsigned char r, g, b;
} Color;

extern const Color RED;
extern const Color GREEN;
extern const Color DARK_GREEN;
extern const Color BLUE;

extern const Color WHITE;
extern const Color BLACK;


Color rgb(unsigned char r, unsigned char g, unsigned char b);

#endif // _COLOR_H_
