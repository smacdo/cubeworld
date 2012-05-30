#ifndef SCOTT_CUBEWORLD_WORLD_GENERATOR_H
#define SCOTT_CUBEWORLD_WORLD_GENERATOR_H

class World;

void makeWorld( const char * type, World& world );
void makeStressfulWorld( World& world );
void makeSimpleWorld( World& world );
void makeFlatWorld( World& world );

#endif
