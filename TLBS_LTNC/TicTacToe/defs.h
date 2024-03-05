#ifndef _DEFS__H

#define _DEFS__H

#include "include.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "hello world";

#define BOARD_X 10
#define BOARD_Y 10
#define CELL_SIZE 30

#define BOARD_SIZE 10
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'


enum media {
    emptyBox,
    oBox,
    xBox
};

#endif