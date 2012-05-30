#ifndef SCOTT_CUBEWORLD_INTERSECTION_H
#define SCOTT_CUBEWORLD_INTERSECTION_H

#include "engine/point.h"
#include "math/vector.h"

#include <limits>

/**
 * Contains information on a potenntial cube intersection
 */
struct CubeIntersection
{
    CubeIntersection()
        : cubepos( -1, -1, -1 ),
          normal( 0, 0, 0 ),
          distance( std::numeric_limits<float>::infinity() )
    {
    }

    Point cubepos;          // Location of the cube that intersected
    Vec3  normal;           // Normal vector at point of intersection
    float distance;         // Distance from ray origin to intersection
};

#endif
