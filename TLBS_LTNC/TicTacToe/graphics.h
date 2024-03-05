#ifndef _GRAPHICS__H

#define _GRAPHICS__H

#include "include.h"
#include "defs.h"
#include "otherFunction.h"
#include "TicTacToe.h"

struct graphics{
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> media;

    graphics(){
    }

    void initSDL(){
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
            logErrorAndExit("INIT SDL: ", SDL_GetError());
        }

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL){
            logErrorAndExit("CREATE WINDOW: ", SDL_GetError());
        }

        renderer = this->createRenderer(window);


        if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "INIT IMG: %s", IMG_GetError());
        }


        
    }

    SDL_Renderer* createRenderer(SDL_Window* window){
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

        if (renderer == NULL){
            logErrorAndExit("Create renderer: ", SDL_GetError());
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        return renderer;
    }

    SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loanding: %s", fileName);

        SDL_Texture* texture = IMG_LoadTexture(renderer, fileName);

        if (texture == NULL){
            logErrorAndExit("Create texture: ", IMG_GetError());
        }

        return texture;
    }

    void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y){
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;

        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }

    void renderMouseBox(graphics& graphic, const int& x, const int& y){
        SDL_Rect box;
        box.w = 10;
        box.h = 10;
        box.x = x-5;
        box.y = y-5;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(renderer, &box);
    }

    void render(const TicTacToe& game){
        // renderTexture(renderer, this->media[emptyBox], 10, 10);
        // renderTexture(renderer, this->media[oBox], 110, 10);
        // renderTexture(renderer, this->media[xBox], 210, 10);
        //prepareScene();

        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j])
                {
                case EMPTY_CELL:
                    renderTexture(renderer, this->media[emptyBox], x, y);
                    break;
                case O_CELL:
                    renderTexture(renderer, this->media[oBox], x, y);
                    break;
                case X_CELL:
                    renderTexture(renderer, this->media[xBox], x, y);
                }
        }

        SDL_RenderPresent(renderer);
    }

    void loadMedia(){
        //media.push_back(this->loadTexture("sources/bikiniBottom.jpg", renderer));
        media.push_back(this->loadTexture("sources/cell_empty.png", renderer));
        media.push_back(this->loadTexture("sources/cell_o.png", renderer));
        media.push_back(this->loadTexture("sources/cell_x.png", renderer));
        return;
    }

    


    void QuitSDL(SDL_Window* window, SDL_Renderer* renderer){
        for (int i = 0; i < this->media.size(); i++){
            SDL_DestroyTexture(this->media[i]);
            this->media[i] == NULL;
        }

        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;

        IMG_Quit();
        SDL_Quit();
    }
};


#endif
