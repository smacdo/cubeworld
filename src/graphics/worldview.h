#ifndef SCOTT_CUBEWORLD_WORLD_VIEW_H
#define SCOTT_CUBEWORLD_WORLD_VIEW_H

class WorldChunk;

/**
 * Contains information on the state of a world, and all the information
 * required to render it correctly to the player
 */
class WorldView
{
public:
    WorldView();
    ~WorldView();

    // Called when a worldchunk is updated, and needs to have it's view
    // reconstructed
    void chunkUpdated( const WorldChunk* chunk ) ;

private:

};

#endif
