#include "engine/material.h"
#include "common/assert.h"
#include <string>

namespace Util
{

std::string ToString( EMaterialType mat )
{
    static const std::string NAMES[ EMATERIAL_COUNT ] =
    {
        "EMPTY",            // EMATERIAL_EMPTY,
        "GRASS",            // EMATERIAL_GRASS,
        "DIRT",             // EMATERIAL_DIRT,
        "ROCK",             // EMATERIAL_ROCK,
        "ORE",              // EMATERIAL_ORE,
        "WATER",            // EMATERIAL_WATER,
        "LAVA",             // EMATERIAL_LAVA,
        "SAND",             // EMATERIAL_SAND,
        "WOOD",             // EMATERIAL_WOOD,
        "TREE",             // EMATERIAL_TREE,
        "LEAF",             // EMATERIAL_LEAF,
    };

    assert( mat < EMATERIAL_COUNT );
    return NAMES[mat];
}

}
