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

    NewMove = &(piece->Move);

    for (int i = 0; i < 15; i++){
        graphic->pieceStepToRenderText[i] = "";
        graphic->gameStep[i] = NULL;
    }

    ply = 0;
    depth = DEPTH;
    alpha = -20000;
    beta = 20000;    
}

void ChineseChess::init(){
    sound_on = true;
    InitData();
    graphic->initSDL();
    explodeSprite->initSprite(graphic->explodeSprite, EXPLODEPIECE_FRAMES, EXPLODEPIECE_CLIPS);
    piece->init();
    piece->texture = graphic->gamePicture[CHESSPIECE];
}

void ChineseChess::switchTurn(){
    turn = (turn == LIGHT) ? DARK : LIGHT;
    xturn = (turn == LIGHT) ? DARK : LIGHT;
}

void ChineseChess::getInput(){
    mouse->getMousePos();
    if (status == START_GAME){
        return;
    }
    
    if (status == WAITING){
        return;
    }

    if (mouse->x < (BOARD_X - 20) || mouse->y < (BOARD_Y - 20) || mouse->x > 563 || mouse->y > 630){
        if (mouse->x > 627 && mouse->x < 627+49 && mouse->y > 521 && mouse->y < 521+52){
            exitQuerry = true;
            status = WAITING;
        }
        if (mouse->x > 627 && mouse->x < 627+49 && mouse->y > 473 && mouse->y < 473+52){
            graphic->SwitchSoundStatus();
            sound_on = (sound_on == true) ? false : true;
        }
        if (mouse->x > 627 && mouse->x < 627+49 && mouse->y > 415 && mouse->y < 415+52){
            getHint();
        }
        return;
    }
    int clickedCol = (mouse->x - (BOARD_X-CELL_SIZE_X/2)) / (CELL_SIZE_X);
    int clickedRow = (mouse->y - (BOARD_Y-CELL_SIZE_Y/2)) / (CELL_SIZE_Y);

    piece->Move.dest = clickedRow * 9 + clickedCol;
}

void ChineseChess::processMenu(){
    mouse->getMousePos();
    if (mouse->x > 240 && mouse->x < 240+228 && mouse->y > 522 && mouse->y < 522+77){
        status = QUIT_GAME;
        quit();
    }
    else if (mouse->x > 240 && mouse->x < 240+228 && mouse->y > 362 && mouse->y < 362+77){
        status = RUNNING;
        gameType = COMPUTER;
    }
    else if (mouse->x > 240 && mouse->x < 240+228 && mouse->y > 445 && mouse->y < 445+77){
        status = RUNNING;
        gameType = PEOPLE;
    }
}

void ChineseChess::getHint(){
    processMove();
}

void ChineseChess::exitGame(){
    if (status == WIN || status == LOSE){
        if (mouse->x > 286 && mouse->x < 323 && mouse->y > 380 && mouse->y < 417){
            piece->init();
            InitData();
        }
        return;
    }

    if (!exitQuerry){
        return;
    }

    if (mouse->x > 185 && mouse->x < 222 && mouse->y > 373 && mouse->y < 409){
        status = RUNNING;
        exitQuerry = false;
    }   
    else if (mouse->x > 373 && mouse->x < 410 && mouse->y > 373 && mouse->y < 409){
        piece->init();
        InitData();
    }
}


void ChineseChess::processClick(){
    if (status == START_GAME){
        processMenu();
        return;
    }

    if (status == WAITING || status == WIN || status == LOSE){
        this->exitGame();
        return;
    }
    
    if (piece->pieceColor[piece->Move.dest] == turn){
        if (piece->Move.from == piece->Move.dest){
            piece->Move = {NONE, NONE};
        }
        piece->Move.from = piece->Move.dest;
        return;
    }
    else{
        if (piece->Move.from != NONE){
            move(piece->Move.from, piece->Move.dest);
            piece->Move = {NONE, NONE};
        }        
    }
}

bool ChineseChess::move(int from, int dest){
    if (ValidStep(from, dest))
    {   
        status = getStatus();
        if (piece->pieceColor[piece->Move.dest] == EMPTY){
            graphic->play(graphic->gameAudio[MOVE_SOUND]);
        }else{
            graphic->play(graphic->gameAudio[KILL_SOUND]);
            exploding = true;
            explode_x = BOARD_X + (dest % 9) * CELL_SIZE_X - 30;
            explode_y = BOARD_Y + (dest / 9) * CELL_SIZE_Y  - 30;   
            explode_pos = dest;
        }

        graphic->MoveToText(from, dest, piece->piecePos[from], turn);

        piece->piecePos[dest] =  piece->piecePos[from];   
        piece->piecePos[from] = EMPTY;

        piece->pieceColor[dest] = turn;
        piece->pieceColor[from] = EMPTY;

        switchTurn();
        return true;
    }
    return false;
}

void ChineseChess::unDoTest(int from, int dest){
    piece->piecePos[dest] = temp_Data[0];
    piece->piecePos[from] = temp_Data[1];
    piece->pieceColor[dest] = temp_Data[2];
    piece->pieceColor[from] = temp_Data[3]; 
}

void ChineseChess::doTest(int from, int dest){
    temp_Data[0] = piece->piecePos[dest];
    temp_Data[1] = piece->piecePos[from];   
    temp_Data[2] = piece->pieceColor[dest];
    temp_Data[3] = piece->pieceColor[from];

    piece->piecePos[dest] =  piece->piecePos[from];   
    piece->piecePos[from] = EMPTY;

    piece->pieceColor[dest] = turn;
    piece->pieceColor[from] = EMPTY;

}

int ChineseChess::getStatus(){
    if (status == WAITING){
        return WAITING;
    }
    if (piece->piecePos[piece->Move.dest] == KING){
        if (piece->pieceColor[piece->Move.dest] == LIGHT){
            return LOSE;
        }
        return WIN;
    }
    return status;
}

bool ChineseChess::isOver(){
    return (Win() || Lose());
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
    if (status != QUIT_GAME){
        return false;
    }
    graphic->QuitSDL();
    return true;
}

bool ChineseChess::ValidStep(int from, int dest){
    gen();
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
    AlphaBeta(alpha, beta, depth);
    getStatus();
    move(piece->Move.from, piece->Move.dest);
    piece->Move = {NONE, NONE};
}

void ChineseChess::render(){
    if (status == RUNNING || status == WIN || status == LOSE || status == WAITING){
        if (!exploding){
            graphic->displayChessPiece(piece); 
        }  
        else{    
            graphic->displayChessPieceExcept(piece, explode_pos);
            graphic->renderPieceExplode(explode_x, explode_y-15, explodeSprite, exploding);    
        }
        graphic->renderTurnSquare(status, turn);
        graphic->renderExit(exitQuerry);
        graphic->renderSoundButton(status, sound_on);
        graphic->displayText();
        if (status == WIN || status == LOSE){
            graphic->renderOverPopUp(status);
        }
    }
    SDL_RenderPresent(graphic->renderer);
}

ChineseChess::~ChineseChess(){
    delete[] arMove;
    arMove = NULL;

    delete[] MoveData;
    MoveData = NULL;

    delete NewMove;
    NewMove = NULL;

    this->piece = NULL;
    this->graphic = NULL;
    this->mouse = NULL;
}