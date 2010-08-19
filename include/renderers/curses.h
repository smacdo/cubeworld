#ifndef SCOTT_ROGUELIKE_RENDERERS_CURSES_H
#define SCOTT_ROGUELIKE_RENDERERS_CURSES_H

class Zone;
class Camera;

void drawTileWorld( const Zone& zone, const Camera& camera, int, int, int, int );

#endif
