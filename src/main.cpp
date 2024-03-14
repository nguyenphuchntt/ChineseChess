#include "../include/headers/logic.h"

bool quit = false;

int main(int arg, char* argv[]){
    std::cout << "hello" << std::endl;

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
    std::cout << "hello" << std::endl;
    return 0;
}
