#ifndef SCOTT_ROGUELIKE_RENDERERS_H
#define SCOTT_ROGUELIKE_RENDERERS_H

namespace Rogue
{
class OctreeWorld;
}
class Camera;

void startRenderer( int argc, char* argv[] );
void stopRenderer();

void renderScene( const Rogue::OctreeWorld& world );
void renderScene( const Rogue::OctreeWorld& world, const Camera& camera );

#endif
