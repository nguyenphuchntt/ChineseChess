#ifndef _DEFS__H
#define _DEFS__H

#include "include.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 640
#define WINDOW_TITLE "Xiangqi"

#define EMPTY                   0
#define LIGHT                   2
#define DARK                    1

#define PAWN                    1
#define BISHOP                  2
#define ELEPHANT                3
#define KNIGHT                  4
#define CANNON                  5
#define ROOK                    6
#define KING                    7

#define BOARD_X 58
#define BOARD_Y 40
#define CELL_SIZE_X 60
#define CELL_SIZE_Y 63

// game status
#define RUNNING 2
#define WAITING 3
#define START_GAME 5
#define QUIT_GAME 4
#define WAITFOREXPLODE 6
#define WIN 1
#define LOSE -1
#define OVER 0

//game type
#define COMPUTER 1
#define PEOPLE 2

#define NONE -100

#define DEPTH 5

const int EXPLODEPIECE_CLIPS[][4] = {
    {3,0,60,65},
    {68,0,60,65},
    {131,0,60,65},
    {193,0,60,65},
    {257,0,60,65},
    {322,0,60,65},
    {386,0,60,65},
    {451,0,60,65},
    {516,0,60,65}
};
const int EXPLODEPIECE_FRAMES = sizeof(EXPLODEPIECE_CLIPS) / sizeof(int) / 4;
#endif
