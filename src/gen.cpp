#include "../include/headers/logic.h"

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