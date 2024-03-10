#ifndef _MOUSE__H

#define _MOUSE__H
#include "defs.h"
#include "graphics.h"

struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    void move() {
        x += dx; y += dy;
    }

    void turnNorth() {
        dy = -speed; dx = 0;
    }
    void turnSouth() {
        dy = speed; dx = 0;
    }
    void turnWest() {
        dy = 0; dx = -speed;
    }
    void turnEast() {
        dy = 0; dx = speed;
    }
};

void render(const Mouse& mouse, const graphics& graphic){
    SDL_Rect pos;
    pos.x = mouse.x;
    pos.y = mouse.y;
    pos.h = 20;
    pos.w = 20;
    SDL_SetRenderDrawColor(graphic.renderer, 255,255,255,0);
    SDL_RenderFillRect(graphic.renderer, &pos);
    // SDL_RenderPresent(graphic.renderer);
}

bool gameOver(const Mouse& mouse){
    if ((mouse.x <= 0 || mouse.x >= SCREEN_WIDTH || mouse.y <= 0 || mouse.y >= SCREEN_HEIGHT)){
        std::cout << "gameOver!"; 
        return true;
    }
    return false;
}   

#endif