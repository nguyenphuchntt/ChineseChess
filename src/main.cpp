#include "../include/headers/logic.h"

Mouse gMouse;
graphics gGraphic;
ChessPiece gPiece;
ChineseChess game;

int main(int arg, char* argv[]){
    
    game.graphic = &gGraphic;
    game.piece = &gPiece;
    game.mouse = &gMouse;
    gGraphic.mouse = &gMouse;
    game.init();
    
    SDL_Event event;
    while (1){
        game.graphic->prepareScene(game.status, game.gameType);
        if (game.turn == DARK){
            game.processMove();
        }
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                game.status = QUIT_GAME;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                if (( game.turn == LIGHT && game.gameType == COMPUTER) 
                   || game.gameType == PEOPLE
                   || game.status == WIN || game.status == LOSE)
                {
                    game.getInput();
                }
                game.processClick();
            }
        }
        game.render();
        // std::cout << game.status << std::endl;
        if (game.quit()) break;
    }
    return 0;
}
