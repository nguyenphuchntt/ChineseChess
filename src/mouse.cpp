#include "../include/headers/mouse.h"



void Mouse::getMousePos(){
    SDL_GetMouseState(&x, &y);
}

