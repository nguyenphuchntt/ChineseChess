#include "../include/headers/graphics.h"


void graphics::initSDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        logErrorAndExit("init SDL", SDL_GetError());
    }
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL){
        logErrorAndExit("create window", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        logErrorAndExit("create renderer", SDL_GetError());
    }
    // SDL_RenderClear(renderer);
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)){
        logErrorAndExit("init IMG", IMG_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        logErrorAndExit("SDL_mixer could not initialize!", Mix_GetError());
    }
    if (TTF_Init() == -1) {
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
    }

    this->loadMedia();    
}

void graphics::prepareScene(int status, int typeGame){
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);    
    if (status == RUNNING || status == WIN || status == LOSE || status == OVER || status == WAITING){
        SDL_RenderCopy(renderer, gamePicture[GAMEBOARD], NULL, NULL);  
        this->renderTexture(gamePicture[HINT], 627, 364);
        if (typeGame == PEOPLE){
            this->renderTexture(gamePicture[DIAGONAL_LINE], 627,374);
        }
        this->renderTexture(gamePicture[UNDO], 623, 419);
        this->renderTexture(gamePicture[EXIT_QUERRY], 627, 521); 
    }
    if (status == START_GAME){
        mouse.getMousePos();
        SDL_RenderCopy(renderer, gamePicture[START_BACK], NULL, NULL);
        if (mouse.x > 240 && mouse.x < 240+228 && mouse.y > 362 && mouse.y < 362+77){
            this->renderTexture(gamePicture[SELECT_MENU], 240+10, 362);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 445);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 522);
        }else if (mouse.x > 240 && mouse.x < 240+228 && mouse.y > 445 && mouse.y < 445+77){
            this->renderTexture(gamePicture[SELECT_MENU], 240+10, 445);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 362);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 522);
        }else if (mouse.x > 240 && mouse.x < 240+228 && mouse.y > 522 && mouse.y < 522+77){
            this->renderTexture(gamePicture[SELECT_MENU], 240+10, 522);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 445);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 362);
        }
        else{
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 445);
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 362);      
            this->renderTexture(gamePicture[UNSELECT_MENU], 240+10, 522);       
        }
        this->renderTexture(gamePicture[ONE_PLAYER], 240, 362);
        this->renderTexture(gamePicture[TWO_PLAYER], 240, 445);
        this->renderTexture(gamePicture[QUIT], 240, 522);
    }

    this->play(backgrounMusic);
}

void graphics::loadMedia(){
    gamePicture.push_back(this->loadTexture("assets/img/1player.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/2player.png"));
    gamePicture.push_back(this->loadTexture("assets/img/black.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/Brown.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/exit.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/gameBoard.png"));
    gamePicture.push_back(this->loadTexture("assets/img/chessPiece.png"));     
    gamePicture.push_back(this->loadTexture("assets/img/gameOverNotification.png"));
    gamePicture.push_back(this->loadTexture("assets/img/hint.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/menu.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/select.png"));
    gamePicture.push_back(this->loadTexture("assets/img/Orange.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/quit.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/red.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/select_menu.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/start_back.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/undo.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/unselect_menu.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/lose.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/win.png"));
    gamePicture.push_back(this->loadTexture("assets/img/music.png")); 
    gamePicture.push_back(this->loadTexture("assets/img/music_pause.png"));
    gamePicture.push_back(this->loadTexture("assets/img/diagonalLine.png"));

    backgrounMusic = this->loadMusic("assets/audio/background_sound.wav");

    gameAudio.push_back(this->loadSound("assets/audio/kill_sound.wav"));
    gameAudio.push_back(this->loadSound("assets/audio/move_sound.wav"));

    gFont = this->loadFont("assets/font/thuPhap.ttf", 200);
    std::cout << "loaded media!" << std::endl;
}

void graphics::freeMedia(){
    for (int i = 0; i < gamePicture.size(); i++){
        SDL_DestroyTexture(gamePicture[i]);
        gamePicture[i] = NULL;
    }
    for (int i = 0; i < gameAudio.size(); i++){
        Mix_FreeChunk(gameAudio[i]);
        gameAudio[i] = NULL;
    }    
    Mix_FreeMusic(backgrounMusic);
    backgrounMusic = NULL;
    
}

SDL_Texture* graphics::loadTexture(const char* fileName){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "loading: %s", fileName);
    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName);
    if (texture == NULL){
        logErrorAndExit("load media", IMG_GetError());
    }
    return texture;
}

Mix_Music* graphics::loadMusic(const char* path){
    Mix_Music* gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "could not load music!", Mix_GetError());
    }
    return gMusic;
}

TTF_Font* graphics::loadFont(const char* path, int size) 
{
    TTF_Font* gFont = TTF_OpenFont( path, size );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}


Mix_Chunk* graphics::loadSound(const char* path){
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "could not load sound!", Mix_GetError());
    }
    return gChunk;
}

void graphics::play(Mix_Music* gMusic){
    if (gMusic == nullptr){
        return;
    }
    if (Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gMusic, -1);
    }
    // else if (Mix_PausedMusic() == 1){
    //     Mix_ResumeMusic();
    // }
}

void graphics::play(Mix_Chunk* gChunk){
    if (gChunk != nullptr){
        Mix_PlayChannel(-1, gChunk, 0);
    }
}

void graphics::renderSoundButton(int gameStatus, bool soundStatus){
    if (gameStatus == QUIT_GAME || gameStatus == START_GAME){
        return;
    }
    this->renderTexture(gamePicture[MUSIC], 627, 473);
    if(!soundStatus){
        this->renderTexture(gamePicture[DIAGONAL_LINE], 627, 473);
    }
}

void graphics::SwitchSoundStatus(){
    if( Mix_PlayingMusic() == 0 ){
        Mix_PlayMusic( backgrounMusic, -1 );
    }else{
        if( Mix_PausedMusic() == 1 ){
            
            Mix_ResumeMusic();
        }else{
            Mix_PauseMusic();
        }
    }
    return;
}

SDL_Texture* graphics::renderText(const char* text, TTF_Font* font, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
    if (textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface );
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface );
    return texture;
}


void graphics::renderTexture(SDL_Texture* texture, int x, int y){
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void graphics::QuitSDL(){
    this->freeMedia();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(gFont);

    renderer = NULL;
    window = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void graphics::renderChessPiece(int n, const ChessPiece& chessPiece) {
    int i = n / 9;
    int j = n % 9;
    SDL_Rect dst;
    dst.x = BOARD_X + j * CELL_SIZE_X - 30;
    dst.y = BOARD_Y + i * CELL_SIZE_Y  - 30;
    dst.w = 60;
    dst.h = 60;
    // std::cout << n << " " << dst.x << " " << dst.y;
    SDL_Rect src;
    if (chessPiece.pieceColor[n] == LIGHT){
        src.x = chessPiece.lightPos[chessPiece.piecePos[n]-1][0];
        src.y = chessPiece.lightPos[chessPiece.piecePos[n]-1][1];
        src.w = chessPiece.lightPos[chessPiece.piecePos[n]-1][2];
        src.h = chessPiece.lightPos[chessPiece.piecePos[n]-1][3];
    }
    else {
        src.x = chessPiece.darkPos[chessPiece.piecePos[n]-1][0];
        src.y = chessPiece.darkPos[chessPiece.piecePos[n]-1][1];
        src.w = chessPiece.darkPos[chessPiece.piecePos[n]-1][2];
        src.h = chessPiece.darkPos[chessPiece.piecePos[n]-1][3];
    }
    if (n == chessPiece.Move.from && chessPiece.Move.from != NONE){
        SDL_Rect d;
        d.x = BOARD_X + j * CELL_SIZE_X - 32;
        d.y = BOARD_Y + i * CELL_SIZE_Y  - 32;
        d.w = 63;
        d.h = 63;
        SDL_RenderCopy(renderer, this->gamePicture[SELECT], NULL, &d);
    }
    // std::cout << "--" << src.x << " " << src.y << " " << src.w << " " << src.h;
    // SDL_QueryTexture(chessPiece.texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, chessPiece.texture, &src, &dst);
    // std::cout << std::endl;
}

void graphics::displayChessPiece(const ChessPiece& chessPiece){
    for (int n = 0; n < 90; n++){
        if ((chessPiece.pieceColor[n] == LIGHT) || (chessPiece.pieceColor[n] == DARK)){
            renderChessPiece(n, chessPiece);       
        }
    }
}

void graphics::renderExit(bool exitQuerry){
    if (!exitQuerry){
        return;
    }
    this->mouse.getMousePos();
    if (this->mouse.x > 185 && this->mouse.x < 222 && this->mouse.y > 373 && this->mouse.y < 409){
        this->renderTexture(this->gamePicture[ORANGE_COLOR], 165, 353);
        this->renderTexture(this->gamePicture[BROWN_COLOR], 365, 360);
    }
    else if (this->mouse.x > 373 && this->mouse.x < 410 && this->mouse.y > 373 && this->mouse.y < 409){
        this->renderTexture(this->gamePicture[BROWN_COLOR], 165, 353);
        this->renderTexture(this->gamePicture[ORANGE_COLOR], 365, 359);        
    }
    else {
        this->renderTexture(this->gamePicture[BROWN_COLOR], 165, 353);
        this->renderTexture(this->gamePicture[BROWN_COLOR], 365, 359);          
    }
    this->renderTexture(this->gamePicture[EXIT], 122, 257);
}

void graphics::renderTurnSquare(int status, int turn){
    if (status != RUNNING){
        return;
    }
    if (turn == LIGHT){
        this->renderTexture(this->gamePicture[RED_SQUARE], 640, 586);
        return;
    }
    this->renderTexture(this->gamePicture[BLACK_SQUARE], 640, 586);
}
    