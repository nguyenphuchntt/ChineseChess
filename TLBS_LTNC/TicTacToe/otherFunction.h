#ifndef _OTHERFUNCTION__H

#define _OTHERFUNCTION__H

#include "include.h"

void logErrorAndExit(const char* mes, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", mes, error);
    SDL_Quit();
}

void waitUntilKeyPressed(){
    SDL_Event e;
    while (true){
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)){
            return;
        }
        SDL_Delay(100);
    }
}


#endif