#include "src/header/include.h"
#include "src/header/defs.h"
#include "src/header/graphics.h"
#include "src/header/function.h"

bool quit = false;

int main(int arg, char* argv[]){
    graphics graphic;
    graphic.initSDL();

    SDL_Event event;
    
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) std::cout << "UP ";
        if (currentKeyStates[SDL_SCANCODE_DOWN]) std::cout << "DOWN ";
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) std::cout << "RIGHT ";
        if (currentKeyStates[SDL_SCANCODE_LEFT]) std::cout << "LEFT ";
        std::cout << "..\n";
        SDL_Delay(100);
    }

    graphic.QuitSDL();
    return 0;
}
