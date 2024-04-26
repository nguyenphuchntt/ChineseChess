#ifndef _SPRITE__H
#define _SPRITE__H

#include "include.h"

struct Sprite{
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currFrame;
    int temp;

    Sprite(){

    }
    void initSprite(SDL_Texture* _texture, int frames, const int _clips[][4]);
    void tick();
    const SDL_Rect* getCurrFrame();
    ~Sprite();
};

#endif //_SPRITE__H