#ifndef _CONFIG_H_
#define _CONFIG_H_

const static int CHAR_WIDTH = 8;
const static int CHAR_HEIGHT = 8;
const static int CHAR_SCALE = 2;

const static char* WINDOW_TITLE = "Simulation";

const static int MAP_WIDTH = 40;
const static int MAP_HEIGHT = 40;
const static int WINDOW_WIDTH = MAP_WIDTH * CHAR_WIDTH * CHAR_SCALE;
const static int WINDOW_HEIGHT = MAP_HEIGHT * CHAR_HEIGHT * CHAR_SCALE;


#endif // _CONFIG_H_
