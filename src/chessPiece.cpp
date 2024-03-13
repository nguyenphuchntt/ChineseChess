#include "../include/headers/chessPiece.h"

void ChessPiece::init(){
    int Pos[90] = {
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

    int Color[90] = {
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
    piecePos = Pos;
    pieceColor = Color;
}

void ChessPiece::switchTurn(){
    turn = (turn == LIGHT) ? DARK : LIGHT;
}

// void ChessPiece::getInput(int pos){
//     if (pieceColor[pos] == 2){
//         selected = pos;
//     }else if (pieceColor[pos] == 1){
//         // selected = -1;
//         this->processClick();
//     }
// }

ChessPiece::~ChessPiece(){
    pieceColor = NULL;
    delete[] pieceColor;

    piecePos = NULL;
    delete[] piecePos;

}