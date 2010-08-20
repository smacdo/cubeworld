#include "cubeworld.h"
#include <vector>

using namespace Rogue;

const int WChunkRows  = 64;
const int WChunkCols  = 64;
const int WChunkDepth = 64;

///////////////////////////////////////////////////////////////////////////
// World handling
///////////////////////////////////////////////////////////////////////////
World::World( int rows, int cols, int depth )
    : m_chunks( rows * cols * depth ),
      m_rows( rows ),
      m_cols( cols ),
      m_depth( depth )
{
    // Sanity - make sure they are correct multiples
    assert( rows  > 0 && rows  % WChunkRows  == 0 );
    assert( cols  > 0 && cols  % WChunkCols  == 0 );
    assert( depth > 0 && depth % WChunkDepth == 0 );

    // Seed the chunk array by setting everything to null
    for ( int i = 0; i < rows * cols * depth; ++i )
    {
        m_chunks[i] = NULL;
    }
}

World::~World()
{
    // Clean up teh world
    for ( int i = 0; i < m_rows * m_cols * m_depth; ++i )
    {
        delete m_chunks[i];
    }
}

void World::put( WorldCube& cube )
{
    // we're just going to pretend there's one chunk for now..
    WorldChunk * chunk = getChunk( 0, 0, 0 );

    chunk->put( cube );
}

WorldCube World::getAt( const Point& position )
{
    WorldChunk * chunk = getChunk( 0, 0, 0 );

    return chunk->getAt( position );
}

bool World::isEmptyAt( const Point& position ) const
{
    WorldChunk * chunk = getChunk( 0, 0, 0 );

    if ( chunk )
    {
        return chunk->isEmptyAt( position );
    }
    else
    {
        return true;
    }
}

std::vector<WorldCube> World::getAllCubes() const
{
    WorldChunk * chunk = getChunk( 0, 0, 0 );
    
    if ( chunk )
    {
        return chunk->getAllCubes();
    }
    else
    {
        return std::vector<WorldCube>();
    }
}

void World::visitAllCubes( CubeVisitor& visitor ) const
{
    WorldChunk * chunk = getChunk( 0, 0, 0 );
    
    if ( chunk )
    {
        chunk->visitAllCubes( visitor );
    }
}

int World::cubeCount() const
{
    WorldChunk * chunk = getChunk( 0, 0, 0 );
    
    if ( chunk )
    {
        return chunk->cubeCount();
    }
    else
    {
        return 0;
    }
}

void World::makeRelativeToChunk( int& row, int& col, int& depth ) const
{
    row   = row   % WChunkRows;
    col   = col   % WChunkCols;
    depth = depth % WChunkDepth;
}

WorldChunk* World::getChunk( int chunk_r, int chunk_c, int chunk_d )
{
    int offset = getChunkOffsetFor( chunk_r, chunk_c, chunk_d );

    if ( m_chunks[offset] == NULL )
    {
        m_chunks[offset] = new WorldChunk();
    }

    return m_chunks[offset];
}

WorldChunk* World::getChunk( int chunk_r, int chunk_c, int chunk_d ) const
{
    return m_chunks[ getChunkOffsetFor( chunk_r, chunk_c, chunk_d ) ];
}

int World::getChunkOffsetFor( int chunk_r, int chunk_c, int chunk_d ) const
{
    // Get correct offsets
    int r = chunk_r / WChunkRows;
    int c = chunk_c / WChunkCols;
    int d = chunk_d / WChunkDepth;

    // todo sanity?
    return ( c + r * WChunkCols ) * ( d * WChunkCols * WChunkRows );
}

///////////////////////////////////////////////////////////////////////////
// World chunk
///////////////////////////////////////////////////////////////////////////
WorldChunk::WorldChunk()
    : m_cubes()
{
    m_cubes.reserve( 128 );
}

WorldChunk::~WorldChunk()
{
}

void WorldChunk::put( WorldCube& cube )
{
    int offset = findCubeOffset( cube );

    // Does it exist in the world?
    if ( offset != -1 )
    {
        // It exists. Overwrite its data field
        m_cubes[offset] = cube;
    }
    else
    {
        // It doesn't exist. Add it
        m_cubes.push_back( cube );
    }
}

// if cube does not exist, adds it
WorldCube WorldChunk::getAt( const Point& position )
{
    WorldCube cube( position );
    int offset = findCubeOffset( cube );

    if ( offset != -1 )
    {
        return m_cubes[offset];
    }
    else
    {
        m_cubes.push_back( cube );
        return cube;
    }
}

bool WorldChunk::isEmptyAt( const Point& position ) const
{
    return findCubeOffsetByPosition( position ) == -1;
}

std::vector<WorldCube> WorldChunk::getAllCubes() const
{
    return std::vector<WorldCube>(m_cubes);
}

void WorldChunk::visitAllCubes( CubeVisitor& visitor ) const
{
    std::vector<WorldCube>::const_iterator itr;

    for ( itr = m_cubes.begin(); itr != m_cubes.end(); ++itr )
    {
        visitor.process( *itr );
    }
}

int WorldChunk::cubeCount() const
{
    return m_cubes.size();
}

int WorldChunk::findCubeOffset( const WorldCube& cube ) const
{
    return findCubeOffsetByPosition( cube.m_position );
}

/**
 * It attempts to locate a cube with the given position. If there is
 * no cube at that location, it will return -1.
 */
int WorldChunk::findCubeOffsetByPosition( const Point& position ) const
{
    std::vector<WorldCube>::const_iterator itr;
    int found  = -1;
    int offset = -1;

    for ( itr = m_cubes.begin(); itr != m_cubes.end(); ++itr )
    {
        offset++;

        if ( itr->m_position == position )
        {
            found = offset;
            break;
        }
    }

    return found;
}
