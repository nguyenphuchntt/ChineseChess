#include "src/header/include.h"
#include "src/header/defs.h"
#include "src/header/graphics.h"
#include "src/header/function.h"
#include "src/header/mouse.h"

bool quit = false;

int main(int arg, char* argv[]){
    graphics graphic;
    graphic.initSDL();


    SDL_Event event;
    while (!quit){
        SDL_SetRenderDrawColor(graphic.renderer, 0,0,0,0);
        SDL_RenderClear(graphic.renderer);



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
