#ifndef _LOGIC__H

#define _LOGIC__H

#include "include.h"
#include "graphics.h"
#include "mouse.h"
#include "move.h"

struct ChineseChess{

    ChessPiece* piece;
    graphics* graphic;
    Mouse* mouse;

    int turn; int xturn;
    int status;
    int gameType;

    bool exitQuerry;
    bool sound_on;


    short*       gen_begin = new short[50];    
    short*       gen_end = new short[50];

    MOVE*        arMove = new MOVE[4096];
    PMOVE        NewMove;
    MOVEDATA*    MoveData = new MOVEDATA[50];

    int temp_Data[4] = {NONE};

    int ply;
    short depth;

    short alpha, beta;

    void InitData();
    void init();
    void getInput();
    void render();

    void processClick();
    void processMenu();
    void exitGame();
    void SetSoundStatus();
    void getHint();

    bool move(int from, int dest);
    void unDoTest(int from, int dest);
    void doTest(int from, int dest);


    void gen();
    bool KingFaceCheck(short from, short dest);
    short AlphaBeta(short alpha, short beta, short depth);
    void processMove();

    bool ValidStep(int from, int dest);

    void switchTurn();

    int getStatus();
    bool isOver();
    bool Win();
    bool Lose();

    bool quit();
    ~ChineseChess();
};



#endif