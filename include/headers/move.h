#ifndef _MOVE__H

#define _MOVE__H

typedef struct
{
    int   from, dest;
} MOVE, *PMOVE;
typedef struct
{
    int   from, dest;
    // int     capture;
} MOVEDATA, *PMOVEDATA;


#endif