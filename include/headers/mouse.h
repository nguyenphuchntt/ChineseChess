#ifndef _MOUSE__H

#define _MOUSE__H

#include "include.h"
struct Mouse{
    int x; int y;

    Mouse(){
        x = 0; y = 0;
    }

    void getMousePos();


};

#endif