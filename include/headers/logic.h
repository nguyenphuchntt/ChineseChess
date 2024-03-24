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
    PMOVE       NewMove;
    MOVEDATA    MoveData[50];

    int ply;
    short depth;

    short alpha, beta;

    void init();
    void quit();
    void getInput();
    void render();
    void processClick();

    bool move(int from, int dest);

    void gen();
    short AlphaBeta(short alpha, short beta, short depth);
    void processMove();

    bool ValidStep(int from, int dest);

    void switchTurn();

    bool isOver();
    bool Win();
    bool Lose();

};



#endif