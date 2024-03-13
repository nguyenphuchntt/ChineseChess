#ifndef _alphaBeta__H

#define _alphaBeta__H

short AlphaBeta(MOVEDATA MoveData[], MOVE Move[], PMOVE newmove, char color[], char piece[], short start[], short end[], char side, char xside, char Ply, short alpha, short beta, short depth)
{
    static  short   hdp;
    short   value, best;
    if (!depth)
    {
        short   piecevalue[7] = {10, 20, 20, 40, 45, 90, 1000};
        short   iEval = 0;
        for (short i = 0; i < 90; i++)      // EVALUATE
        {
            if (color[i] == side)
                iEval += piecevalue[piece[i]];
            else if (color[i] == xside)
                iEval -= piecevalue[piece[i]];
        }
        return iEval;
    }
    Gen(color, piece, start, end, Ply, side, xside, Move);
    best = -20000;
    for (short i=start[Ply]; i<end[Ply] && best<beta; i++)
    {
        if (best > alpha)
            alpha = best;
        // Thực hiện đi thử
        short from, dest, p;
        from = Move[i].from;
        dest = Move[i].dest;
        MoveData[hdp].dest = Move[i].dest;
        MoveData[hdp].from = Move[i].from;
        MoveData[hdp].capture = p = piece[dest];
        piece[dest] = piece[from];
        piece[from] = EMPTY;
        color[dest] = color[from];
        color[from] = EMPTY;
        hdp++;
        Ply++;
        side = xside;
        xside = 1 - xside;
        if (p == KING)
            value = 1000 - Ply;
        else
            value = -AlphaBeta(MoveData, Move, newmove, color, piece, start, end, side, xside, Ply, -beta, -alpha, depth-1);
        // Hoàn lại nước đi thử
        hdp--;
        Ply--;
        side = xside;
        xside = 1 - xside;
        from = MoveData[hdp].from;
        dest = MoveData[hdp].dest;
        piece[from] = piece[dest];
        color[from] = color[dest];
        piece[dest] = MoveData[hdp].capture;
        if (piece[dest] == EMPTY)
            color[dest] = EMPTY;
        else
            color[dest] = xside;
        // Nếu là nước đi tốt hơn thì nhận dữ liệu nước đi
        if (value > best)
        {
            best = value;
            if (!Ply)
            {
                newmove->dest = Move[i].dest;
                newmove->from = Move[i].from;
            }
        }
    }
    return best;
}

#endif