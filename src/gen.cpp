#include "../include/headers/logic.h"

void ChineseChess::gen(){
    gen_end[ply] = gen_begin[ply];
    for (int i = 0; i < 90; i++)
    {
    if (piece->pieceColor[i] != turn) continue;
    int p = piece->piecePos[i];
    for (int j = 0; j < 8; j++){ // maximum direction
        if (!piece->Offset[p][j]) break;
        short x = piece->Mailbox90[i]; // used to convert from mailbox90 to large box
        char fCannon = 0;
        char n; // the number of possible ways in one direction
        if (p == ROOK || p == CANNON) n = 9;
        else                          n = 1;
        for (char k = 0; k < n; k++){
            if (p == PAWN && turn == LIGHT) x -= piece->Offset[p][j]; // because PAWN must move forward
            else                            x += piece->Offset[p][j];
            short y = piece->Largebox[x]; // convert mailbox90 to largebox: y = value of x in largeBox = dest of possible step
            char t = ((turn == DARK) ? y : (89 - y)); // because legalPos just describe for one side
            if (y == -1 || (piece->Legalposition[t] & piece->Maskpiece[p]) == 0) break;
            if (KingFaceCheck(i, y)) break;
            if (!fCannon)
            {
                if (piece->pieceColor[y] != turn){ // this piece is xturn's piece or empty
                    switch (p){
                        case KNIGHT:
                            this->KnightCheck(i, y, j);
                        break;
                        case ELEPHANT:
                            this->ElephantCheck(i, y, j);
                        break;
                        case CANNON:
                            if (piece->pieceColor[y] == EMPTY)// because cannon can not eat other piece directly
                            {
                                arMove[gen_end[ply]].from = i;
                                arMove[gen_end[ply]].dest = y;
                                gen_end[ply]++;
                            }
                            break;
                        default:
                        // delete KingCheck
                            arMove[gen_end[ply]].from = i;
                            arMove[gen_end[ply]].dest = y;
                            gen_end[ply]++;
                            break;
                    }                        
                }
                if (piece->pieceColor[y] != EMPTY){
                    if (p == CANNON) fCannon++;
                    else             break;
                }
            }
            else{ // if fCannon == 1
                if (piece->pieceColor[y] != EMPTY){
                    if (piece->pieceColor[y] == xturn){
                        arMove[gen_end[ply]].from = i; // move at the end
                        arMove[gen_end[ply]].dest = y;
                        gen_end[ply]++;
                    }
                    break;
                }
            }
        }
    }        
    }
    gen_end[ply + 1] = gen_end[ply]; // must be added to recursion call, the data will not be overlap
    gen_begin[ply + 1] = gen_end[ply];
    // the number of subMove is created after each function call is gen_end[ply] - gen_begin[ply]
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

void ChineseChess::KnightCheck(int from, int dest, int currDirection){
    if (piece->pieceColor[from + piece->Knightcheck[currDirection]] == EMPTY){   
        arMove[gen_end[ply]].from = from;
        arMove[gen_end[ply]].dest = dest;
        gen_end[ply]++;
    }
}

void ChineseChess::ElephantCheck(int from, int dest, int currDirection){
    if (piece->pieceColor[from + piece->Elephancheck[currDirection]] == EMPTY){
        arMove[gen_end[ply]].from = from;
        arMove[gen_end[ply]].dest = dest;
        gen_end[ply]++;       
    }
}
