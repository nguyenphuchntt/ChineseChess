#include "../include/headers/logic.h"

bool quit = false;

int main(int arg, char* argv[]){
    int status = 1;

    graphics graphic;
    graphic.initSDL();
    
    ChessPiece piece;
    piece.init();
    piece.texture = graphic.gameMedia[CHESSPIECE]; 

    graphic.prepareScene();
    
    SDL_Event event;
    while (!quit){
        
		
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        graphic.displayChessPiece(status, piece);
        SDL_RenderPresent(graphic.renderer);
        // SDL_Delay(100);


    }
    graphic.QuitSDL();
    return 0;
}
