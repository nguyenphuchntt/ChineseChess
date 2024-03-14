#include "../include/headers/chessPiece.h"

void ChessPiece::init(){
    turn = LIGHT;
    selected = -1;

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
}