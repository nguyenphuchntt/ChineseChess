#include "../include/headers/logic.h"

void ChineseChess::init(){
    status = START;
    turn = LIGHT;

    graphic.initSDL();
    piece.texture = this->graphic.gameMedia[CHESSPIECE];

}

void ChineseChess::switchTurn(){
    turn = (turn == LIGHT) ? DARK : LIGHT;
}

void ChineseChess::getInput(){
    this->mouse.getMousePos();
    if (this->mouse.x < (BOARD_X - 20) || this->mouse.y < (BOARD_Y - 20) || this->mouse.x > 563 || this->mouse.y > 630){
        return;
    }
    int clickedCol = (this->mouse.x - (BOARD_X-CELL_SIZE_X/2)) / (CELL_SIZE_X);
    int clickedRow = (this->mouse.y - (BOARD_Y-CELL_SIZE_Y/2)) / (CELL_SIZE_Y);
    // std::cout << clickedCol << " " << clickedRow;
    this->piece.tmp_selected = clickedRow * 9 + clickedCol;

    // std::cout << " " << pos << std::endl;
}

void ChineseChess::processClick(){
    if (this->piece.pieceColor[this->piece.tmp_selected] == turn){
        this->piece.selected = this->piece.tmp_selected;
        return;
    }
    else{
        if (this->piece.selected != EMPTY){
            if (this->ValidStep()){
                this->move(this->piece.selected, this->piece.tmp_selected);
            }        
            this->piece.selected = EMPTY;   
        }
    
    }

    // if (this->piece.pieceColor[this->piece.tmp_selected] == EMPTY && this->piece.selected != EMPTY){
    //     if (this->ValidStep()){
    //         this->move(this->piece.selected, this->piece.tmp_selected);
    //     }        
    //     this->piece.selected = EMPTY;
    //     return;
    // }
    // if (this->piece.pieceColor[this->piece.tmp_selected] == DARK && this->piece.selected != EMPTY){
    //     if (this->ValidStep()){
    //         this->move(this->piece.selected, this->piece.tmp_selected);
    //     }
    //     this->piece.selected = EMPTY;    
    // }    
}

void ChineseChess::move(int from, int dest){
    this->piece.piecePos[dest] =  this->piece.piecePos[from];
    this->piece.piecePos[from] = EMPTY;

    this->piece.pieceColor[dest] = turn;
    this->piece.pieceColor[from] = EMPTY;
    
    this->switchTurn();
}

bool ChineseChess::ValidStep(){
    return true;
}