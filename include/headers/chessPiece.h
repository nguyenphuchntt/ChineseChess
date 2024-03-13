#ifndef _CHESSPIECE__H
#define _CHESSPIECE__H

#include "include.h"

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