#ifndef SCOTT_CUBEWORLD_WORLD_CHUNK_MESH_H
#define SCOTT_CUBEWORLD_WORLD_CHUNK_MESH_H

#include <vector>

#include "graphics/cubevertex.h"

struct WorldChunkMesh
{
    std::vector<CubeVertex> vertices;
    std::vector<unsigned int> indices;
};

#endif
