#include "../include/headers/chessPiece.h"

void ChessPiece::init(){
    Move = {NONE, NONE};
    int color[90] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 2, 0, 2, 0, 2, 0, 2,
    0, 2, 0, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2    
    };     
    int pos[90] = {
    6, 4, 3, 2, 7, 2, 3, 4, 6,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 5, 0, 0, 0, 0, 0, 5, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 5, 0, 0, 0, 0, 0, 5, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    6, 4, 3, 2, 7, 2, 3, 4, 6};

    for (int i = 0; i < 90; i++){
        pieceColor[i] = color[i];
        piecePos[i] = pos[i];
    }

}


ChessPiece::~ChessPiece(){
    pieceColor = NULL;
    delete[] pieceColor;
    piecePos = NULL;
    delete[] piecePos;
}