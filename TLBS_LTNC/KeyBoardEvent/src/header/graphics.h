#ifndef _GRAPHICS__H

#define _GRAPHICS__H

#include "function.h"
#include "defs.h"

struct graphics{
    SDL_Window* window = NULL; 
    SDL_Renderer* renderer = NULL;

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

        if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)){
            logErrorAndExit("init IMG", IMG_GetError());
        }
    }

    void QuitSDL(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        renderer = NULL;
        window = NULL;

        IMG_Quit();
        SDL_Quit();
        
    }

};

#endif