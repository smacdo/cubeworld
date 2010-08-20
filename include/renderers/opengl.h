#ifndef SCOTT_ROGUELIKE_RENDERERS_H
#define SCOTT_ROGUELIKE_RENDERERS_H

namespace Rogue
{
class World;
}
class Camera;

void startRenderer( int argc, char* argv[] );
void stopRenderer();

void renderScene( /*const*/ Rogue::World& world );
void renderScene( /*const*/ Rogue::World& world, const Camera& camera );

#endif
