#include "../include/headers/include.h"
#include "../include/headers/defs.h"
#include "../include/headers/graphics.h"
#include "../include/headers/function.h"
#include "../include/headers/chessPiece.h"
#include "../include/headers/logic.h"

// #include "include/headers/include.h"
// #include "include/headers/defs.h"
// #include "include/headers/graphics.h"
// #include "include/headers/function.h"
// #include "include/headers/chessPiece.h"
// #include "include/headers/logic.h"

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
