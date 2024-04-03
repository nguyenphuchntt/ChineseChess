#include "../include/headers/logic.h"

void ChineseChess::InitData(){
    status = START_GAME;
    gameType = WAITING;
    turn = LIGHT;
    xturn = DARK;

    exitQuerry = false;

    for (int i = 0; i < 50; i++){
        gen_begin[i] = 0;
        gen_end[i] = 0;
    }

    MOVEDATA MoveData_[50] = {0};
    for (int i = 0; i < 50; i++){
        MoveData[i] = MoveData_[i];
    }

    MOVE arMove_[4096] = {0};
    for (int i = 0; i < 4096; i++){
        arMove[i] = arMove_[i];
    }

    NewMove = &(this->piece.Move);

    for (int i = 0; i < 15; i++){
        graphic.pieceStepToRenderText[i] = "";
        graphic.gameStep[i] = NULL;
    }

    ply = 0;
    depth = DEPTH;
    alpha = -20000;
    beta = 20000;    
}

void ChineseChess::init(){
    sound_on = true;

    this->InitData();

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
    if (status == START_GAME){
        return;
    }
    
    if (status == WAITING){
        return;
    }

    if (this->mouse.x < (BOARD_X - 20) || this->mouse.y < (BOARD_Y - 20) || this->mouse.x > 563 || this->mouse.y > 630){
        if (mouse.x > 627 && mouse.x < 627+49 && mouse.y > 521 && mouse.y < 521+52){
            exitQuerry = true;
            this->status = WAITING;
        }
        if (mouse.x > 627 && mouse.x < 627+49 && mouse.y > 473 && mouse.y < 473+52){
            this->graphic.SwitchSoundStatus();
            sound_on = (sound_on == true) ? false : true;
        }
        if (mouse.x > 627 && mouse.x < 627+49 && mouse.y > 364 && mouse.y < 364+52){
            this->getHint();
        }
        return;
    }
    int clickedCol = (this->mouse.x - (BOARD_X-CELL_SIZE_X/2)) / (CELL_SIZE_X);
    int clickedRow = (this->mouse.y - (BOARD_Y-CELL_SIZE_Y/2)) / (CELL_SIZE_Y);

    this->piece.Move.dest = clickedRow * 9 + clickedCol;
}

void ChineseChess::processMenu(){
    mouse.getMousePos();
    if (mouse.x > 240 && mouse.x < 240+228 && mouse.y > 522 && mouse.y < 522+77){
        this->status = QUIT_GAME;
        this->quit();
    }
    else if (mouse.x > 240 && mouse.x < 240+228 && mouse.y > 362 && mouse.y < 362+77){
        this->status = RUNNING;// bug
        this->gameType = COMPUTER;
    }
    else if (mouse.x > 240 && mouse.x < 240+228 && mouse.y > 445 && mouse.y < 445+77){
        this->status = RUNNING;
        this->gameType = PEOPLE;
    }
}

void ChineseChess::getHint(){
    this->processMove();
}

void ChineseChess::exitGame(){
    if (status == WIN || status == LOSE){
        if (this->mouse.x > 286 && this->mouse.x < 323 && this->mouse.y > 380 && this->mouse.y < 417){
            piece.init();
            this->InitData();
        }
        return;
    }

    if (!exitQuerry){
        return;
    }

    if (this->mouse.x > 185 && this->mouse.x < 222 && this->mouse.y > 373 && this->mouse.y < 409){
        status = RUNNING;
        exitQuerry = false;
    }   
    else if (this->mouse.x > 373 && this->mouse.x < 410 && this->mouse.y > 373 && this->mouse.y < 409){
        piece.init();
        this->InitData();
    }
}


void ChineseChess::processClick(){
    if (status == START_GAME){
        this->processMenu();
        return;
    }
    if (status == WIN || status == LOSE){
        return;
    }
    if (status == WAITING){
        return;
    }
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
        status = this->getStatus();
        if (this->piece.pieceColor[this->piece.Move.dest] == EMPTY){
            this->graphic.play(this->graphic.gameAudio[MOVE_SOUND]);
        }else{
            this->graphic.play(this->graphic.gameAudio[KILL_SOUND]);
        }

        this->graphic.MoveToText(from, dest, this->piece.piecePos[from], turn);

        this->piece.piecePos[dest] =  this->piece.piecePos[from];   
        this->piece.piecePos[from] = EMPTY;

        this->piece.pieceColor[dest] = turn;
        this->piece.pieceColor[from] = EMPTY;

        this->switchTurn();
        return true;
    }
    return false;
}

void ChineseChess::unDoTest(int from, int dest){
    this->piece.piecePos[dest] = temp_Data[0];
    this->piece.piecePos[from] = temp_Data[1];
    this->piece.pieceColor[dest] = temp_Data[2];
    this->piece.pieceColor[from] = temp_Data[3]; 
}

void ChineseChess::doTest(int from, int dest){
    temp_Data[0] = this->piece.piecePos[dest];
    temp_Data[1] = this->piece.piecePos[from];   
    temp_Data[2] = this->piece.pieceColor[dest];
    temp_Data[3] = this->piece.pieceColor[from];

    this->piece.piecePos[dest] =  this->piece.piecePos[from];   
    this->piece.piecePos[from] = EMPTY;

    this->piece.pieceColor[dest] = turn;
    this->piece.pieceColor[from] = EMPTY;

}

int ChineseChess::getStatus(){
    if (status == WAITING){
        return WAITING;
    }
    if (this->piece.piecePos[this->piece.Move.dest] == KING){
        if (this->piece.pieceColor[this->piece.Move.dest] == LIGHT){
            return LOSE;
        }
        return WIN;
    }
    return this->status;
}

bool ChineseChess::isOver(){
    return (this->Win() || this->Lose());
}

bool ChineseChess::Win(){
    if (status == WIN){
        std::cout << "win";
        return true;
    }
    return false;
}

bool ChineseChess::Lose(){
    if (status == LOSE){
        std::cout << "lose";
        return true;
    }
    return false;
}

bool ChineseChess::quit(){
    if (this->status != QUIT_GAME){
        return false;
    }
    this->~ChineseChess();
    this->graphic.QuitSDL();
    return true;
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
    if (status == START_GAME || gameType == PEOPLE || status == WIN || status == LOSE){
        return;
    }
    this->AlphaBeta(alpha, beta, depth);
    this->getStatus();
    this->move(this->piece.Move.from, this->piece.Move.dest);
    this->piece.Move = {NONE, NONE};
}

void ChineseChess::render(){
    if (status == RUNNING || status == WIN || status == LOSE || status == WAITING){
        graphic.displayChessPiece(this->piece);  
        graphic.renderTurnSquare(status, turn);
        graphic.renderExit(exitQuerry);
        graphic.renderSoundButton(status, sound_on);
        graphic.displayText();
        if (status == WIN || status == LOSE){
            this->graphic.renderOverPopUp(status);
        }
        if (status == WAITING || status == WIN || status == LOSE){
            this->exitGame();
        }
    }
    SDL_RenderPresent(this->graphic.renderer);
}