#include "rogue.h"
#include "coredefs.h"

#include "renderers/opengl.h"
#include "gameapp.h"

int main( int argc, char* argv[] )
{
    runGame();
    startRenderer( argc, argv );

    stopRenderer();
    return 0;
}
