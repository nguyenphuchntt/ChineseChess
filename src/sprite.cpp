#include "../include/headers/sprite.h"

void Sprite::initSprite(SDL_Texture* _texture, int frames, const int _clips[][4]){
    int temp = 0;
    int currFrame = 0;
    texture = _texture;
    SDL_Rect clip;
    for (int i = 0; i < frames; i++){
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];
        clips.push_back(clip);
    }
}
void Sprite::tick(){
    temp++;
    if (temp % 3 == 0) {
        currFrame = (currFrame + 1) % clips.size();
    }
}

const SDL_Rect* Sprite::getCurrFrame(){
    return &(clips[currFrame]);
}

Sprite::~Sprite(){
    texture = NULL;
    std::cout << "sprite cleaned!" << std::endl;
}