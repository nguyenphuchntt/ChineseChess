#include "../include/headers/logic.h"

void ChineseChess::gen(){
    gen_end[ply] = gen_begin[ply];
    for (int i = 0; i < 90; i++)
    {
    if (piece->pieceColor[i] == turn){
        int p = piece->piecePos[i];
        for (int j = 0; j < 8; j++){
            if (!piece->Offset[p][j]) break;
            short x = piece->Mailbox90[i]; // used to convert from mailbox90 to large box
            char fCannon = 0;
            char n; // the number of possible ways in one direction
            if (p == ROOK || p == CANNON) n = 9;
            else                          n = 1;
            for (char k = 0; k < n; k++){
                if (p == PAWN && turn == LIGHT) x -= piece->Offset[p][j]; // because PAWN must move forward
                else                            x += piece->Offset[p][j];
                short y = piece->Largebox[x]; // convert mailbox90 to largebox
                char t = ((turn == DARK) ? y : (89 - y)); // because legalPos just describe for one side
                if (y == -1 || (piece->Legalposition[t] & piece->Maskpiece[p]) == 0) break;
                if (KingFaceCheck(i, y)) break;
                if (!fCannon)
                {
                if (piece->pieceColor[y] != turn){
                    switch (p){
                        case KNIGHT:
                        if (piece->pieceColor[i + piece->Knightcheck[j]] == EMPTY)
                        {   
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;

                        }
                        break;
                        case ELEPHANT:
                        if (piece->pieceColor[i + piece->Elephancheck[j]] == EMPTY)
                        {
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;       
                        }
                        break;
                        case CANNON:
                            if (piece->pieceColor[y] == EMPTY)
                            {
                                arMove[gen_end[ply]].from = i;
                                arMove[gen_end[ply]].dest = y;
                                gen_end[ply]++;
                            }
                            break;
                        default:
                            if (!KingFaceCheck(i, y))
                            {
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;
                            break;
                            }
                        }                        
                    }
                    if (piece->pieceColor[y] != EMPTY){
                        if (p == CANNON) fCannon++;
                        else             break;
                    }
                }
                else{
                    if (piece->pieceColor[y] != EMPTY){
                        if (piece->pieceColor[y] == xturn){
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

bool ChineseChess::KingFaceCheck(short from, short dest){
    doTest(from, dest);
    for (int n = 0; n < 90; n++){
        if (piece->piecePos[n] == KING){
            for (int p = n + 9; p < 88; p += 9){
                if (piece->piecePos[p] != EMPTY && piece->piecePos[p] != KING){  
                    unDoTest(from, dest);
                    return false;
                }else if (piece->piecePos[p] == KING){
                    unDoTest(from, dest);
                    return true;
                }
            }
            break;
        }
    }
    unDoTest(from, dest);
    return false;
}