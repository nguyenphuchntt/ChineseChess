#ifndef _CHESSPIECE__H
#define _CHESSPIECE__H

#include "include.h"
#include "defs.h"
struct ChessPiece{
    ChessPiece(){
    }

    SDL_Texture* texture;

    int* piecePos = new int[90];
    int* pieceColor = new int[90];

    int turn = LIGHT;
    int selected = -1;

    void init();
    void getInput(int pos);
    bool processClick();

    void move(int from, int dest);
    void undo(int dest, int from);

    bool ValidStep();

    void switchTurn();
    
    ~ChessPiece();

};


#endif