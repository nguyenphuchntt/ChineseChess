#include "../include/headers/logic.h"

void ChineseChess::init(){
    status = START;
    turn = LIGHT;
    xturn = DARK;

    gen_begin[50] = { 0 };
    gen_end[50] = { 0 };

    arMove[4096] = { 0 };
    MoveData[50] = { 0 };

    NewMove = &(this->piece.Move);

    ply = 0;
    depth = DEPTH;
    alpha = -20000;
    beta = 20000;

    graphic.initSDL();
    piece.init();
    piece.texture = this->graphic.gamePicture[CHESSPIECE];

}

void ChineseChess::quit(){
    this->graphic.QuitSDL();
}

void ChineseChess::switchTurn(){
    turn = (turn == LIGHT) ? DARK : LIGHT;
    xturn = (turn == LIGHT) ? DARK : LIGHT;
}

void ChineseChess::getInput(){
    this->mouse.getMousePos();
    if (this->mouse.x < (BOARD_X - 20) || this->mouse.y < (BOARD_Y - 20) || this->mouse.x > 563 || this->mouse.y > 630){
        return;
    }
    int clickedCol = (this->mouse.x - (BOARD_X-CELL_SIZE_X/2)) / (CELL_SIZE_X);
    int clickedRow = (this->mouse.y - (BOARD_Y-CELL_SIZE_Y/2)) / (CELL_SIZE_Y);

    this->piece.Move.dest = clickedRow * 9 + clickedCol;
}

void ChineseChess::processClick(){
    if (this->piece.pieceColor[this->piece.Move.dest] == turn){
        if (this->piece.Move.from == this->piece.Move.dest){
            this->piece.Move = {NONE, NONE};
        }
        this->piece.Move.from = this->piece.Move.dest;
        return;
    }
    else{
        if (this->piece.Move.from != NONE){
            this->move(this->piece.Move.from, this->piece.Move.dest);
            this->piece.Move = {NONE, NONE};
        }        

    }
}

bool ChineseChess::move(int from, int dest){
    
    if (this->ValidStep(from, dest))
    {
        this->piece.piecePos[dest] =  this->piece.piecePos[from];
        this->piece.piecePos[from] = EMPTY;

        this->piece.pieceColor[dest] = turn;
        this->piece.pieceColor[from] = EMPTY;

        this->switchTurn();
        return true;
    }
    return false;
}


bool ChineseChess::isOver(){
    // return (this->Win() || this->Lose());
    return false;
}


bool ChineseChess::ValidStep(int from, int dest){
    this->gen();
    for (int i = gen_begin[0]; i < gen_end[0]; i++){
        if (arMove[i].from == from && arMove[i].dest == dest){
            return true;
        }
    }
    return false;
}


void ChineseChess::processMove(){
    this->AlphaBeta(alpha, beta, depth);
    this->move(this->piece.Move.from, this->piece.Move.dest);
    this->piece.Move = {NONE, NONE};
}

void ChineseChess::render(){
    this->graphic.displayChessPiece(this->piece);
}