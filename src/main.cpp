#include "../include/headers/logic.h"

bool quit = false;

int main(int arg, char* argv[]){
    ChineseChess game;
    game.init(); 
    
    SDL_Event event;
    while (!quit){
        game.graphic.prepareScene();
        
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                game.getInput();
                game.processClick();
            }
        }
        
        game.graphic.displayChessPiece(game.piece);
        SDL_RenderPresent(game.graphic.renderer);
        // SDL_GetMouseState(&x, &y);
        // std::cout << "--" << x << " " << y << std::endl;
        // SDL_Delay(500);
    }
    game.graphic.QuitSDL();
    return 0;
}
