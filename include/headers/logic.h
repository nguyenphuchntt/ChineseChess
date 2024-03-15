#ifndef _LOGIC__H

#define _LOGIC__H

#include "include.h"
#include "graphics.h"

struct ChineseChess{

    ChessPiece piece;
    graphics graphic;
    Mouse mouse;

    int turn;
    int status;

    void init();
    void getInput();
    void processClick();

    void move(int from, int dest);
    void undo(int dest, int from);

    bool ValidStep();

    void switchTurn();

};



#endif