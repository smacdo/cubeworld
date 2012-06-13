#ifndef SCOTT_CUBEWORLD_WORLD_H
#define SCOTT_CUBEWORLD_WORLD_H

#include "engine/point.h"
#include "math/vector.h"
#include "engine/cubeintersection.h"
#include <vector>

class WorldView;
class CubeData;
class WorldChunk;

/**
 * Contains the cubes and entities that exist in a world
 */
class World
{
public:
    World( unsigned int cols,
           unsigned int rows,
           unsigned int depth,
           WorldView * pView );
    ~World();

    // Place a cube
    void put( const CubeData& cube,
              const Point& position,
              bool createIfNull=true);

    // Retrieve a cube
    CubeData at( const Point& position,
                 bool createIfNull=true );

    // Retrieve a cube
    CubeData at( const Point& position ) const;

    // Find the first cube that intersects our ray
    CubeIntersection firstCubeIntersecting( const Vec3& origin,
                                            const Vec3& dir );

    // Checks if position is empty
    bool isEmptyAt( const Point& position ) const;

    unsigned int rows() const  { return mRows; }
    unsigned int cols() const  { return mCols; }
    unsigned int depth() const { return mDepth; }

    // Returns number of instantiated chunks
    unsigned int chunkCount() const;

    // Finds the number of non-empty cubes
    unsigned int cubeCount() const;

protected:
    WorldChunk* getChunkForPos( const Point& pos,
                                bool createIfNull=true);
    const WorldChunk* getChunkForPos( const Point& pos ) const;

    Point makeRelativeToChunk( const Point& pos ) const;
    inline unsigned int getIndexForChunk( const Point& pos ) const;

protected:
    WorldView * mpView;
    std::vector<WorldChunk*> mChunks;
    unsigned int mCols;     // x
    unsigned int mRows;     // y
    unsigned int mDepth;    // z
};

#endif
