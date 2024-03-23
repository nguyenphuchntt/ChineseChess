#ifndef _LOGIC__H

#define _LOGIC__H

#include "include.h"
#include "graphics.h"
#include "mouse.h"
#include "move.h"

struct ChineseChess{

    ChessPiece piece;
    graphics graphic;
    Mouse mouse;

    int turn; int xturn;
    int status;

    short       gen_begin[50];    
    short       gen_end[50];

    MOVE        arMove[4096];
    MOVEDATA    MoveData[50];

    int ply;

    void init();
    void getInput();
    void processClick();

    void move(int from, int dest);
    void undo(int dest, int from);

    void gen();

    bool ValidStep(int from, int dest);

    void switchTurn();

    bool isOver();
    bool Win();
    bool Lose();

};



#endif