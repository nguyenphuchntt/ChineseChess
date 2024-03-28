#include "../include/headers/logic.h"

bool quit = false;

int main(int arg, char* argv[]){
    ChineseChess game;
    game.init(); 
    
    SDL_Event event;
    while (!quit){
        game.graphic.prepareScene(game.status);
        if (game.turn == DARK && game.gameType == ONE_PLAYER){
            game.processMove();
        }
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if ((game.turn == LIGHT && game.gameType == ONE_PLAYER) || game.gameType == TWO_PLAYER){
                    game.getInput();
                }
                game.processClick();
            }
        }
        // std::cout << game.status << " ";
        game.render();
        if (game.quit()) break;
    }
    return 0;
}
