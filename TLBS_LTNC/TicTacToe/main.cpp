#include "graphics.h"
#include "defs.h"
#include "include.h"
#include "otherFunction.h"
#include "TicTacToe.h"


int main(int arg, char* argv[]){
	graphics graphic = graphics();
	graphic.initSDL();
	graphic.loadMedia();
	SDL_RenderClear(graphic.renderer);
	
	TicTacToe game;
	game.init();

	graphic.render(game);
	SDL_RenderPresent(graphic.renderer);

	int x_pos, y_pos;

	bool quit = false;
	while (!quit){

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x_pos, &y_pos);
				std::cout << "DOWN AT: " << x_pos << " " << y_pos << std::endl;
				game.processClickAt(x_pos, y_pos);
				graphic.render(game);
			}
			if (e.type == SDL_MOUSEBUTTONUP){
				std::cout << "UP AT: " << x_pos << " " << y_pos << std::endl;
			}
		}
		SDL_RenderPresent(graphic.renderer);
	}

	graphic.QuitSDL(graphic.window, graphic.renderer);
	return 0;
}