#ifndef _DEFS__H

#define _DEFS__H


const int SCREEN_WIDTH = 826;
const int SCREEN_HEIGHT = 551;
const char* WINDOW_TITLE = "SDL";




int BIRD_CLIPS[][4] = {
    {34,0,147,143},
    {216,0,147,143},
    {400,0,147,143},
    {557,0,169,143},
    {726,0,184,143},
    {34,221,147,122}
};

const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;

#endif