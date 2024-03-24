#include "../include/headers/logic.h"

bool quit = false;

int main(int arg, char* argv[]){
    ChineseChess game;
    game.init(); 
    
    SDL_Event event;
    while (!quit){
        game.graphic.prepareScene();
        if (game.turn == DARK){
            game.processMove();
        }
        while (SDL_PollEvent(&event)){

            if (event.type == SDL_QUIT){
                quit = true;
            }
            if (game.turn == LIGHT){ 
                if (event.type == SDL_MOUSEBUTTONDOWN){
                    game.getInput();
                    game.processClick();
                }                
            }
        }
        game.render();
        SDL_RenderPresent(game.graphic.renderer);

    }
    game.quit();
    return 0;
}
