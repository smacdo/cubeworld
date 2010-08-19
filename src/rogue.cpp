
#include "rogue.h"
#include "coredefs.h"

#include "point.h"
#include "camera.h"
#include "zone.h"
#include "player.h"

#include "renderers/opengl.h"
#include "gameworld.h"
#include "gameapp.h"

int main( int argc, char* argv[] )
{
    runGame();
    startRenderer( argc, argv );

/*    initscr();

    Zone zone = getWorldZone();
    Camera cam( Point(2, 2,0), Point(8,8,0) );

    drawTileWorld( zone, cam, 0, 0, 16, 16 );

    refresh();
    getch();
    endwin();*/

    stopRenderer();

    return 0;
}
