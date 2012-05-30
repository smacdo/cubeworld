#ifndef SCOTT_CUBEWORLD_WORLDCUBE_H
#define SCOTT_CUBEWORLD_WORLDCUBE_H

#include "engine/point.h"
#include "engine/cubedata.h"

/**
 * WorldCube is a convenience structure that holds both a cube's data
 * and it's location in the world
 */
struct WorldCube
{
    WorldCube( const CubeData& cubeData_,
               const Point& pos_ )
        : cubeData( cubeData_ ),
          pos( pos_ )
    {
    }

    CubeData cubeData;
    Point pos;
};

#endif
