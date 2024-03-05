
#include "def.h"
#include "include.h"

void waitUntilKeyPressed(){
	SDL_Event e;
	while (true){
		if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)){
			return;
		}
		SDL_Delay(100);
	}
}

int main(int arg, char* argv[]){
	std::cout << "Hello world";


    return 0;
}