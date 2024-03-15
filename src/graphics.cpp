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
    this->loadMedia();    
}

void graphics::prepareScene(){
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, gameMedia[GAMEBOARD], NULL, NULL);    
}

void graphics::loadMedia(){
    gameMedia.push_back(this->loadTexture("assets/img/gameBoard.png"));
    gameMedia.push_back(this->loadTexture("assets/img/chessPiece.png"));
    std::cout << "load media successful!" << std::endl;
}

void graphics::freeMedia(){
    for (int i = 0; i < gameMedia.size(); i++){
        SDL_DestroyTexture(gameMedia[i]);
        gameMedia[i] = NULL;
    } 
}

SDL_Texture* graphics::loadTexture(const char* fileName){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "loading: %s", fileName);
    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName);
    if (texture == NULL){
        logErrorAndExit("load media", IMG_GetError());
    }
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
    renderer = NULL;
    window = NULL;

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
    // std::cout << "--" << src.x << " " << src.y << " " << src.w << " " << src.h;
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
