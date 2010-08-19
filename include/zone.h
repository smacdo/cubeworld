#ifndef SCOTT_ROGUELIKE_ZONE_H
#define SCOTT_ROGUELIKE_ZONE_H

#include "coredefs.h"

struct Zone
{
    Zone( int w, int h, Tile* t )
        : width(w), height(h), tiles(t)
    {
    }

    int width;
    int height;
    Tile * tiles;
};



#endif
