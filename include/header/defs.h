#ifndef _DEFS__H


#define _DEFS__H

#include "include.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 640;
const char* WINDOW_TITLE = "Xiangqi";

const int chessPiecePos[][4]{
    //den
    {4,4,60,60},//tuong
    {71,4,60,60},//si
    {138,4,60,60},//tuong
    {205,4,60,60},//xe
    {272,4,60,60},//ma
    {205,70,60,60},//tot
    {272,70,60,60},//phao
    // do
    {4,135,60,60}, // tuong
    {71,135,60,60}, //si
    {138,135,60,60}, //tuong
    {205,200,60,60}, // xe    
    {272,200,60,60}, // ma
    {138,200,60,60}, // tot    
    {339,135,60,60} // phao
};

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


#endif
