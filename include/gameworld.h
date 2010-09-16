#ifndef SCOTT_ROGUELIKE_WORLD_H
#define SCOTT_ROGUELIKE_WORLD_H

namespace Rogue
{
    class World;
}

void makeWorld( const char * type, Rogue::World& world );
void makeStressfulWorld( Rogue::World& world );
void makeSimpleWorld( Rogue::World& world );
void makeFlatWorld( Rogue::World& world );

#endif
