#ifndef SCOTT_CUBEWORLD_CUBE_VERTEX_H
#define SCOTT_CUBEWORLD_CUBE_VERTEX_H

#include <stdint.h>
#include <cstddef>
#include <vector>

#include "math/vector.h"

struct CubeVertex
{
    CubeVertex( const Vec3& p, const Vec3& n, const Vec3& t )
    {
        pos[0]    = p[0]; pos[1]    = p[1]; pos[2]    = p[2];
        normal[0] = n[0]; normal[1] = n[1]; normal[2] = n[2];
        tex[0]    = t[0]; tex[1]    = t[1];
    }

    float pos[3];           // 4x3 --> 12 / 12
    float normal[3];        // 4x3 --> 12 / 24
    float tex[2];           // 4x2 -->  8 / 32
};

#endif
