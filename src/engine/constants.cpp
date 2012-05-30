#include "engine/constants.h"

// Project wide constantrs and whatnot
namespace Constants
{
    unsigned int CHUNK_COLS  = 32;   // Width of a chunk along x axis
    unsigned int CHUNK_ROWS  = 32;   // Width of a chunk along y axis
    unsigned int CHUNK_DEPTH = 32;   // Width of a chunk along z axis
    unsigned int CHUNK_CUBES = CHUNK_COLS * CHUNK_ROWS * CHUNK_DEPTH;
}
