#ifndef _GRAPHICS__H

#define _GRAPHICS__H

#include "media.h"
#include "chessPiece.h"
#include "function.h"
struct graphics{
    SDL_Window* window = NULL; 
    SDL_Renderer* renderer = NULL;
    std::vector<SDL_Texture*> gameMedia;

    graphics(){
    }

    void initSDL(){
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
            logErrorAndExit("init SDL", SDL_GetError());
        }

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    void prepareScene(){
        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameMedia[GAMEBOARD], NULL, NULL);
    }

    void loadMedia(){
        gameMedia.push_back(this->loadTexture("assets/img/gameBoard.png"));
        gameMedia.push_back(this->loadTexture("assets/img/chessPiece.png"));
        std::cout << "load media successful!";
    }

    void freeMedia(){
        for (int i = 0; i < gameMedia.size(); i++){
            SDL_DestroyTexture(gameMedia[i]);
            gameMedia[i] = NULL;
        }
    }

    SDL_Texture* loadTexture(const char* fileName){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "loading: %s", fileName);
        SDL_Texture* texture = IMG_LoadTexture(renderer, fileName);
        if (texture == NULL){
            logErrorAndExit("load media", IMG_GetError());
        }
        return texture;
    }

    void renderTexture(SDL_Texture* texture, int x, int y){
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);


        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }

    void QuitSDL(){
        this->freeMedia();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        renderer = NULL;
        window = NULL;

        IMG_Quit();
        SDL_Quit();
        
    }

};

#endif