#ifndef _FUNCTION__H

#define _FUNCTION__H

#include "graphics.h"
#include "include.h"

void waitUntilKeyPressed(){
    SDL_Event e;
    while (true){
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)){
            return;
        }
    }
    SDL_Delay(100);
}

void logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

#endif