#include "../include/headers/logic.h"

void ChineseChess::init(){
    status = START;
    turn = LIGHT;
    xturn = DARK;

    gen_begin[50] = { 0 };
    gen_end[50] = { 0 };

    arMove[4096] = { 0 };
    MoveData[50] = { 0 };

    ply = 0;

    graphic.initSDL();
    piece.init();
    piece.texture = this->graphic.gamePicture[CHESSPIECE];

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
    // std::cout << clickedCol << " " << clickedRow;
    this->piece.tmp_selected = clickedRow * 9 + clickedCol;

    // std::cout << " " << pos << std::endl;
}

void ChineseChess::processClick(){
    if (this->piece.pieceColor[this->piece.tmp_selected] == turn){
        if (this->piece.selected == this->piece.tmp_selected){
            this->piece.selected = NONE;
            this->piece.tmp_selected = NONE;
        }
        this->piece.selected = this->piece.tmp_selected;
        return;
    }
    else{
        if (this->piece.selected != NONE){
            if (this->ValidStep(this->piece.selected, this->piece.tmp_selected)){
                this->move(this->piece.selected, this->piece.tmp_selected);
            }        
            this->piece.selected = NONE;   
        }

    }

}

void ChineseChess::move(int from, int dest){




    this->piece.piecePos[dest] =  this->piece.piecePos[from];
    this->piece.piecePos[from] = EMPTY;

    this->piece.pieceColor[dest] = turn;
    this->piece.pieceColor[from] = EMPTY;
    
    this->switchTurn();

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


void ChineseChess::gen(){
    gen_end[ply] = gen_begin[ply];
    for (int i = 0; i < 90; i++)
    {
    if (this->piece.pieceColor[i] == turn){
        int p = this->piece.piecePos[i];
        for (int j = 0; j < 8; j++){
            if (!this->piece.Offset[p][j]) break;
            short x = this->piece.Mailbox90[i]; // used to convert from mailbox90 to large box
            char fCannon = 0;
            char n; // the number of possible ways in one direction
            if (p == ROOK || p == CANNON) n = 9;
            else                          n = 1;
            for (char k = 0; k < n; k++){
                if (p == PAWN && turn == LIGHT) x -= this->piece.Offset[p][j]; // because PAWN must move forward
                else                            x += this->piece.Offset[p][j];
                short y = this->piece.Largebox[x]; // convert mailbox90 to largebox
                char t = ((turn == DARK) ? y : (89 - y)); // because legalPos just describe for one side
                if (y == -1 || (this->piece.Legalposition[t] & this->piece.Maskpiece[p]) == 0) break;
                if (!fCannon)
                {
                if (this->piece.pieceColor[y] != turn){
                    switch (p){
                        case KNIGHT:
                        if (this->piece.pieceColor[i + this->piece.Knightcheck[j]] == EMPTY)
                        {
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;
                        }
                        break;
                        case ELEPHANT:
                        if (this->piece.pieceColor[i + this->piece.Elephancheck[j]] == EMPTY)
                        {
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;                            
                        }
                        break;
                        case CANNON:
                            if (this->piece.pieceColor[y] == EMPTY)
                            {
                                arMove[gen_end[ply]].from = i;
                                arMove[gen_end[ply]].dest = y;
                                gen_end[ply]++;
                            }
                            break;
                        default:
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;
                        }                        
                    }
                    if (this->piece.pieceColor[y] != EMPTY){
                        if (p == CANNON) fCannon++;
                        else             break;
                    }
                }
                else{
                    if (this->piece.pieceColor[y] != EMPTY){
                        if (this->piece.pieceColor[y] == xturn){
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;
                        }
                        break;
                    }
                }
                }
            }
        }
    }
    gen_end[ply + 1] = gen_end[ply];
    gen_begin[ply + 1] = gen_end[ply];
}
