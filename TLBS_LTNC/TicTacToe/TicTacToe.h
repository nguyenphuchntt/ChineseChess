#ifndef _TICTACTOE__H

#define _TICTACTOE__H

struct TicTacToe{
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;

    void init() {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
    }

    void move(int row, int column) {
        if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE)
        {
            board[row][column] = nextMove;
            nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
        }
    }

    void processClickAt(int x, int y) {
        int clickedCol = (x - BOARD_X) / CELL_SIZE;
        int clickedRow = (y - BOARD_Y) / CELL_SIZE;
        this->move(clickedRow, clickedCol);    
    }

};


#endif