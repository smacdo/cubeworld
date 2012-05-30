#ifndef SCOTT_CUBEWORLD_OPENGL_RENDERER
#define SCOTT_CUBEWORLD_OPENGL_RENDERER

class Camera;
class World;

void startRenderer( int argc, char* argv[] );
void stopRenderer();

void renderScene( const World& world );
void renderScene( const World& world, const Camera& camera );

#endif
