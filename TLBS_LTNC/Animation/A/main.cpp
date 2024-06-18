#include "src/header/include.h"
#include "src/header/defs.h"
#include "src/header/graphics.h"
#include "src/header/function.h"
#include "src/header/mouse.h"

bool quit = false;

int main(int arg, char* argv[]){
    graphics graphic;
    graphic.initSDL();

    Mouse mouse;
    mouse.x = SCREEN_WIDTH/2;
    mouse.y = SCREEN_HEIGHT/2;

    SDL_Event event;
    
    while (!quit && !gameOver(mouse)){
        SDL_SetRenderDrawColor(graphic.renderer, 0,0,0,0);
        SDL_RenderClear(graphic.renderer);

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) mouse.turnNorth();
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) mouse.turnSouth();
                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) mouse.turnEast();
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) mouse.turnWest();
            }
        }

        // const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        // if (currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        // if (currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        // if (currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();
        // if (currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        // std::cout << "..\n";

        mouse.move();
        render(mouse, graphic);

        SDL_RenderPresent(graphic.renderer);
        SDL_Delay(10);


    }

    graphic.QuitSDL();
    return 0;
}
