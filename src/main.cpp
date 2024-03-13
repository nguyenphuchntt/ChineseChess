#include "../include/header/include.h"
#include "../include/header/defs.h"
#include "../include/header/graphics.h"
#include "../include/header/function.h"
#include "../include/header/chessPiece.h"
#include "../include/header/logic.h"


bool quit = false;

int main(int arg, char* argv[]){
    
    ChessPiece piece;
    piece.init();

    graphics graphic;
    graphic.initSDL();


    SDL_Event event;
    while (!quit){
		graphic.prepareScene();

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        SDL_RenderPresent(graphic.renderer);
        // SDL_Delay(100);


    }

    graphic.QuitSDL();
    return 0;
}
