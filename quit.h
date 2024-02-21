#ifndef _Quit__H

#define _Quit__H

#include <include.h>

void Quit(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    
    SDL_Quit();
    IMG_Quit();
}


#endif 