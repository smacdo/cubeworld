#ifndef SCOTT_CUBEWORLD_MATERIAL_TYPE_H
#define SCOTT_CUBEWORLD_MATERIAL_TYPE_H

#include <iosfwd>
#include <string>

/**
 * Base materials for the game
 */
enum EMaterialType
{
    EMATERIAL_EMPTY,         // this is air, by default
    EMATERIAL_BEDROCK,
    EMATERIAL_GRASS,
    EMATERIAL_DIRT,
    EMATERIAL_ROCK,
    EMATERIAL_ORE,
    EMATERIAL_WATER,
    EMATERIAL_LAVA,
    EMATERIAL_SAND,
    EMATERIAL_WOOD,
    EMATERIAL_TREE,
    EMATERIAL_LEAF,
    EMATERIAL_COUNT
};

namespace Util
{
    std::string ToString( EMaterialType mat );
}

#endif
