#include "engine/world.h"
#include "engine/worldchunk.h"
#include "engine/constants.h"
#include "engine/point.h"
#include "graphics/iworldview.h"
#include <vector>
#include <limits>

/**
 * World constructor
 *
 * \param  cols   World width in cubes (x dimension), must be % 32
 * \param  rows   World height in cubes (y dimension), must be % 32
 * \param  depth  World depth in cubes (z dimension), must be % 32
 */
World::World( unsigned int cols, unsigned int rows, unsigned int depth )
    : mpView( NULL ),
      mChunks( rows * cols * depth, 0 ),
      mCols( cols ),
      mRows( rows ),
      mDepth( depth )
{
    // Sanity - make sure they are correct multiples
    assert( rows  % Constants::CHUNK_ROWS  == 0 );
    assert( cols  % Constants::CHUNK_COLS  == 0 );
    assert( depth % Constants::CHUNK_DEPTH == 0 );
}

/**
 * Destructor
 */
World::~World()
{
    // We need to destroy the view before we can delete the world's chunks
    delete mpView;

    // Clean up teh world
    for ( unsigned int i = 0; i < mRows * mCols * mDepth; ++i )
    {
        delete mChunks[i];
    }
}

/**
 * Place a cube into the world. If a cube already exists at this point, it
 * will be replaced. If it does not exit, a new chunk will potentially be
 * created.
 *
 * \param  cube  The cube data to place
 * \param  pos   The position to place the cube at
 */
void World::put( const CubeData& cube, const Point& pos, bool createIfNull )
{
    WorldChunk* pChunk = getChunkForPos( pos, createIfNull );
    pChunk->put( cube, makeRelativeToChunk( pos ) );

    // Inform the view that the chunk has (potentially) changed
    mpView->chunkUpdated( pChunk );
}

/**
 * Retrieve a cube in the world. If there is no cube at this location, a new
 * chunk will potentially be created, the new cube spawned and returned.
 *
 * \param  pos  The position to retrieve
 */
CubeData World::at( const Point& pos, bool createIfNull )
{
    WorldChunk * pChunk = getChunkForPos( pos, createIfNull );
    return pChunk->at( makeRelativeToChunk( pos ) );
}

/**
 * Retrieve a cube in the world. If there is no cube at this location, a new
 * chunk will potentially be created, the new cube spawned and returned.
 *
 * \param  pos  The position to retrieve
 */
CubeData World::at( const Point& pos ) const
{
    const WorldChunk * pChunk = getChunkForPos( pos );
    assert( pChunk != NULL && "Associated chunk was not created" );

    return pChunk->at( makeRelativeToChunk( pos ) );
}

/**
 * Checks if there exists a cube at the requested location. No chunks will
 * be created, even if the point does not have a containing chunk.
 */
bool World::isEmptyAt( const Point& pos ) const
{
    const WorldChunk * pChunk = getChunkForPos( pos );

    if ( pChunk != NULL )
    {
        return pChunk->isEmptyAt( makeRelativeToChunk( pos ) );
    }
    else
    {
        return true;
    }
}

/**
 * Calculate the number of created chunks in the world
 */
unsigned int World::chunkCount() const
{
    unsigned int count = 0;

    for ( size_t i = 0; i < mChunks.size(); ++i )
    {
        if ( mChunks[i] != NULL )
        {
            count++;
        }
    }

    return count;
}

/**
 * Calculate the number of non-empty cubes in the world
 */
unsigned int World::cubeCount() const
{
    unsigned int count = 0;

    for ( size_t i = 0; i < mChunks.size(); ++i )
    {
        if ( mChunks[i] != NULL )
        {
            count += mChunks[i]->cubeCount();
        }
    }

    return count;
}

CubeIntersection World::firstCubeIntersecting( const Vec3& origin,
                                               const Vec3& dir )
{
    // BROKEN
    WorldChunk * pChunk = getChunkForPos( Point(0, 0, 0) );    // broken
    
    assert( pChunk != NULL && "Could not retrieve chunk information" );
    return pChunk->firstCubeIntersecting( origin, dir );
}

/**
 * Converts a world coordinate into one a point that is relative to a given
 * world chunk's origin
 */
Point World::makeRelativeToChunk( const Point& pos ) const
{
    return Point( pos.x % Constants::CHUNK_COLS,
                  pos.y % Constants::CHUNK_ROWS,
                  pos.z & Constants::CHUNK_DEPTH );
}

/**
 * Retrieve the world chunk that contains the cube in the requested
 * position
 */
WorldChunk* World::getChunkForPos( const Point& pos, bool createIfNull )
{
    unsigned int index = getIndexForChunk( pos );

    // Instantiate a chunk if it hasn't already been created
    if ( mChunks[index] == NULL && createIfNull )
    {
        mChunks[index] = new WorldChunk;
    }

    // Return the chunk
    return mChunks[index];
}

const WorldChunk* World::getChunkForPos( const Point& pos ) const
{
    return mChunks[ getIndexForChunk( pos ) ];
}

/**
 * Looks up a world position and returns an index into mChunks. That world
 * chunk is the one that contains the requested world position
 */
unsigned int World::getIndexForChunk( const Point& pos ) const
{
    // Get correct offsets
    unsigned int x = pos.x / Constants::CHUNK_COLS;
    unsigned int y = pos.y / Constants::CHUNK_ROWS;
    unsigned int z = pos.z / Constants::CHUNK_DEPTH;

    return ( z * Constants::CHUNK_COLS * Constants::CHUNK_ROWS ) +
           ( y * Constants::CHUNK_COLS + x );
}

