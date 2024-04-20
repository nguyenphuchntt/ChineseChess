#ifndef _GRAPHICS__H

#define _GRAPHICS__H

#include "media.h"
#include "chessPiece.h"
#include "exception.h"
#include "mouse.h"
#include "sprite.h"
struct graphics{
    SDL_Window* window = NULL; 
    SDL_Renderer* renderer = NULL;
    Mix_Music* backgrounMusic = NULL;
    TTF_Font* gFont = NULL;

    std::vector<SDL_Texture*> gamePicture;
    std::vector<Mix_Chunk*> gameAudio;
    std::string pieceStepToRenderText[15] = {""};
    std::vector<SDL_Texture*> gameStep = {15, NULL};
    SDL_Texture* explodeSprite = NULL;

    const SDL_Color RED = {255, 0, 0, 255};
    const SDL_Color BLACK = {0,0,0,255};

    Mouse* mouse;

    graphics(){
    }

    void initSDL();
    void prepareScene(int type, int typeGame);

    void loadMedia();
    void freeMedia();

    TTF_Font* loadFont(const char* path, int size);
    SDL_Texture* loadTexture(const char* fileName);
    Mix_Music* loadMusic(const char* path);
    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk* gChunk);
    void play(Mix_Music* gMusic);
    void SwitchSoundStatus();

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);
    void renderTexture(SDL_Texture* texture, int x, int y);
    void renderExit(bool exitQuerry);
    void renderSelectionPiece(const int& n, const ChessPiece* chessPiece);
    void renderTurnSquare(int status, int turn);
    void renderSoundButton(int gameStatus, bool soundStatus);
    void renderHintButton(int gameStatus);
    void renderUndoButton(int gameStatus);
    void renderOverPopUp(int gameStatus);
    void renderStartMenu();

    void renderPieceExplode(int x, int y, Sprite* sprite, bool& exploding);

    void MoveToText(int from, int dest, int pieceType, int side);
    void displayText();
    
    void QuitSDL();

    void renderChessPiece(int n, const ChessPiece* chessPiece);
    void renderChessPiece(int from, int PieceType, int PieceColor, const ChessPiece* chessPiece);
    void displayChessPiece(const ChessPiece* chessPiece);
    void displayChessPieceExplode(const ChessPiece* chessPiece, int from, int dest, int pieceType, int pieceColor);
};

#endif