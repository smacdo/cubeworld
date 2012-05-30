#ifndef SCOTT_CUBEWORLD_WORLD_CHUNK_MESH_H
#define SCOTT_CUBEWORLD_WORLD_CHUNK_MESH_H

#include <stdint.h>
#include <cstddef>
#include <vector>

#include "math/vector.h"

struct WorldChunkMesh
{
    CubeChunkMesh( unsigned int vbo_id,
                   unsigned int ibo_id,
                   size_t faceCount )
        : vbid( vbo_id ),
          ibid( ibo_id ),
          faceCount( faceCount )
    {
    }

    unsigned int vbid;
    unsigned int ibid;
    size_t faceCount;
};

#endif
