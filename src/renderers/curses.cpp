#include "renderers/curses.h"
#include <ncurses.h>

#include "zone.h"
#include "point.h"
#include "camera.h"

void drawTileWorld( const Zone& zone,
                    const Camera& cam,
                    int renderTopX,
                    int renderTopY,
                    int renderCols,
                    int renderRows )
{
    int maxViewWidth  = 4;
    int maxViewHeight = 4;

    int rangeTopX = cam.center().x() - (maxViewWidth/2);
    int rangeTopY = cam.center().y() - (maxViewHeight/2);
    int rangeBotX = cam.center().x() + (maxViewWidth/2);
    int rangeBotY = cam.center().y() + (maxViewHeight/2);

    int worldStartX  = ( rangeTopX > 0 ? rangeTopX : 0 );
    int worldStartY  = ( rangeTopY > 0 ? rangeTopY : 0 );
    int worldStopX   = ( rangeBotX > zone.width ? zone.width : rangeBotX )+1;
    int worldStopY   = ( rangeBotY > zone.height? zone.height: rangeBotY )+1;

    int maxRowsToRender = (worldStopX > renderRows ? renderRows : worldStopX);
    int maxColsToRender = (worldStopY > renderCols ? renderCols : worldStopY);

    for ( int row = 0; row < maxRowsToRender; ++row )
    {
        for ( int col = 0; col < maxColsToRender; ++col )
        {
            int drawAtX = renderTopX + col;
            int drawAtY = renderTopY + row;

            mvaddch( drawAtX, drawAtY, '0' + zone.tiles[row*zone.width+col] );
        }
    }
}
