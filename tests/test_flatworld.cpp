#include <googletest/googletest.h>
#include "engine/world.h"
#include "graphics/null/nullrenderer.h"
#include "graphics/worldview.h"
#include "generation/flatworldgenerator.h"

// This is a simple test case that exists simply to verify that our world
// generator is acting correctly (not crashing, not leaking memory, etc)
TEST(FlatWorldGeneration,Create)
{
    FlatWorldGenerator gen;
    gen.generate( 128, 256, 64, new NullWorldView  );
}
