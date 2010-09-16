#include "cubeworld.h"
#include <vector>
#include <limits>

#include "math/point.h"

using namespace Rogue;

const int WChunkRows  = 32;
const int WChunkCols  = 32;
const int WChunkDepth = 32;

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

CubeIntersection World::firstCubeIntersecting( const Vec3& origin,
                                               const Vec3& dir )
{
    WorldChunk * chunk = getChunk( 0, 0, 0 );
    
    if ( chunk )
    {
        return chunk->firstCubeIntersecting( origin, dir );
    }
    else
    {
        assert( false );
    }
}

CubeChunkMesh* World::getCompiledMesh()
{
    static CubeChunkMesh* mesh = NULL;
    WorldChunk * chunk         = getChunk( 0, 0, 0 );

    if ( mesh == NULL && chunk != NULL )
    {
        mesh  = new CubeChunkMesh( -1, -1, 0 );
        *mesh = chunk->createCompiledMesh();
    }
    
    return mesh;   
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

float intersects( const Vec3& min,
                  const Vec3& max,
                  const Vec3& rayOrigin,
                  const Vec3& rayDir,
                        Vec3& surfaceNormal )
{
    // Surface normals lookup
    static Vec3 axes[3] = { Vec3( 1.0f, 0.0f, 0.0f ),
                            Vec3( 0.0f, 1.0f, 0.0f ),
                            Vec3( 0.0f, 0.0f, 1.0f ) };

    float tmin = std::numeric_limits<float>::min();
    float tmax = std::numeric_limits<float>::max();
    float t1, t2;

    char maxNormSet = 0, minNormSet = 0;

    Vec3 maxNormal, minNormal;

    // Intersect ray with x/y/z slabs
    for ( int k = 0; k < 3; ++k )
    {
        // check the ray against planes xk = -dx_k, xk = dx_k
        if ( rayDir[k] != 0.0f )
        {
            t1 = ( min[k] - rayOrigin[k] ) / rayDir[k];
            t2 = ( max[k] - rayOrigin[k] ) / rayDir[k];

            tmin = std::max( tmin, std::min( t1, t2 ) );
            tmax = std::min( tmax, std::max( t1, t2 ) );

            if ( t1 > ZERO_DELTA && tmin == t1 )  // -face
            {
                minNormal  = -axes[k];
                minNormSet = 1;
            }
            else if ( t2 > ZERO_DELTA && tmin == t2 ) // +face
            {
                minNormal  = axes[k];
                minNormSet = 1;
            }
            else if ( t1 > ZERO_DELTA && tmax == t1 ) // -face
            {
                maxNormal  = -axes[k];
                maxNormSet = 1;
            }
            else if ( t2 > ZERO_DELTA && tmax == t2 ) // +face
            {
                maxNormal  = -axes[k];
                maxNormSet = 1;
            }
        }
        else
        {
            if (( rayOrigin[k] < min[k] ) || ( rayOrigin[k] > max[k] ))
            {
                // not sure what happened here?
                //   out of bounds
                return std::numeric_limits<float>::infinity();
            }
        }
    }   // end for (axes...)

    // tmin..tmax now define the intersectino with parallelpiped
    if ( tmin >= tmax )
    {
        // intersection point is empty or a point
        //   (looks like the ray didn't even hit us)
        return std::numeric_limits<float>::infinity();
    }
    else if ( tmin > ZERO_DELTA )
    {
        if ( minNormSet != 1 )
        {
            std::cout << "tmin=" << tmin << ", tmax=" << tmax << std::endl;
            std::cout << "rd[0]=" << rayDir[0] << ", rd[1]=" << rayDir[1]
                      << ", rd[2]=" << rayDir[2] << std::endl;
            std::cout << "minNormSet=" << (int) minNormSet 
                      << ", maxNormSet=" << (int) maxNormSet << std::endl;
        }
        assert( minNormSet );
        surfaceNormal = minNormal;

        return tmin;
    }
    else if ( tmax > ZERO_DELTA )
    {
        assert( maxNormSet == 1 );
        surfaceNormal = maxNormal;

        return tmax;
    }
    else
    {
        // no hit
        return std::numeric_limits<float>::infinity();
    }
}

CubeIntersection WorldChunk::firstCubeIntersecting( const Vec3& origin,
                                                    const Vec3& dir     )
{
    std::vector<WorldCube>::const_iterator itr;

    //
    // Keep track of information about the intersection
    //
    float minDist  = std::numeric_limits<float>::max();
    CubeIntersection intersection;

    //
    // Search through all cubes to find any cube that might intersect
    // this ray
    //   (TODO: Look up how to partition space so we don't actually
    //          have to examine each cube)
    //
    Vec3 normal;
    float infinity = std::numeric_limits<float>::infinity();
    float dist     = 0.0f;

    for ( itr = m_cubes.begin(); itr != m_cubes.end(); ++itr )
    {
        Point p = itr->position();

        //
        // Test if this cube intersects the ray
        //
        dist = intersects( Vec3( p[0], p[1], p[2] ),
                           Vec3( p[0] + 1.0, p[1] + 1.0, p[2] + 1.0 ),
                           origin,
                           dir,
                           normal
        );
          
        if ( dist == infinity )
        {
            // Nope, didn't intersect...
            continue;
        }

        //
        // Is this the closest one so far?
        //
        if ( dist < minDist )
        {
            minDist = dist;

            // Keep track of best hit
            intersection.cubepos  = p;
            intersection.normal   = normal;
            intersection.distance = dist;
        }
    }

    return intersection;
}

// TODO remove this from worldchunk, use a visitAllCubes()
// visitor pattern to build the mesh
CubeChunkMesh WorldChunk::createCompiledMesh() const
{
    CubeMeshBuilder builder;

    //
    // Cube positions
    //   TODO: rearrange these to fit correct builder pattern
    //      (ABCD, not ADCB)
    // [AB        
    //  DC]    -->  ADCB    
    //
    //   xyz
    //   1. right
    //   2. left
    //   3. back
    //   4. front
    //   5. top
    //   6. bottom
    Vec3 CubePos[6][4] = 
    {
        {   /* right */
            Vec3( 1.0f, 1.0f, 0.0f ),
            Vec3( 1.0f, 0.0f, 0.0f ),
            Vec3( 1.0f, 0.0f,-1.0f ),
            Vec3( 1.0f, 1.0f,-1.0f )
        },
        {   /* left */
            Vec3( 0.0f, 1.0f,-1.0f ),
            Vec3( 0.0f, 0.0f,-1.0f ),
            Vec3( 0.0f, 0.0f, 0.0f ),
            Vec3( 0.0f, 1.0f, 0.0f )
        },
        {   /* back */
            Vec3( 1.0f, 1.0f,-1.0f ),
            Vec3( 1.0f, 0.0f,-1.0f ),
            Vec3( 0.0f, 0.0f,-1.0f ),
            Vec3( 0.0f, 1.0f,-1.0f )
        },
        {   /* front */
            Vec3( 0.0f, 1.0f, 0.0f ),
            Vec3( 0.0f, 0.0f, 0.0f ),
            Vec3( 1.0f, 0.0f, 0.0f ),
            Vec3( 1.0f, 1.0f, 0.0f )
        },
        {   /* top */
            Vec3( 1.0f, 1.0f, 0.0f ),
            Vec3( 1.0f, 1.0f,-1.0f ),
            Vec3( 0.0f, 1.0f,-1.0f ),
            Vec3( 0.0f, 1.0f, 0.0f )
        },
        {   /* bottom */
            Vec3( 0.0f, 0.0f, 0.0f ),
            Vec3( 0.0f, 0.0f,-1.0f ),
            Vec3( 1.0f, 0.0f,-1.0f ),
            Vec3( 1.0f, 0.0f, 0.0f )
        }
    };

    Vec3 CubeNormals[6] =
    {
        Vec3( 1.0f,  0.0f,  0.0f ),
        Vec3(-1.0f,  0.0f,  0.0f ),
        Vec3( 0.0f,  0.0f, -1.0f ),
        Vec3( 0.0f,  0.0f,  1.0f ),
        Vec3( 0.0f,  1.0f,  0.0f ),
        Vec3( 0.0f, -1.0f,  0.0f )
    };

    //
    // Directional mapper
    //   (in game space)
    //  1. +x   -->   right
    //  2. -x   -->   left
    //  3. +y   -->   back
    //  4. -y   -->   front
    //  5. +z   -->   top
    //  6. -z   -->   bottom
    //
    Vec3 axes[6] = { Vec3( 1.0f, 0.0f, 0.0f ),
                     Vec3(-1.0f, 0.0f, 0.0f ),
                     Vec3( 0.0f, 1.0f, 0.0f ),
                     Vec3( 0.0f,-1.0f, 0.0f ),
                     Vec3( 0.0f, 0.0f, 1.0f ),
                     Vec3( 0.0f, 0.0f,-1.0f ) };

    //
    // Okay, walk through each cube
    //
    std::vector<WorldCube>::const_iterator itr;
    int hiddenCubes = 0;
    int hiddenFaces = 0;
    int totalFaces  = 0;

    std::cout << "Starting compile" << std::endl;

    for ( itr = m_cubes.begin(); itr != m_cubes.end(); ++itr )
    {
        Point p = itr->position();

        //
        // Check each side of the cube to see if it has a neighbor
        //
        int hidden = 0;

        for ( int k = 0; k < 6; ++k )
        {
            totalFaces++;

            Point n = Point( p[0] + axes[k][0],
                             p[1] + axes[k][1],
                             p[2] + axes[k][2] );
            Vec3  b = Vec3( p[0], p[2], -p[1] );

            if ( isEmptyAt( n ) )
            {
                // ADCB
                builder.addFace( b + CubePos[k][0], CubeNormals[k],
                                 b + CubePos[k][1], CubeNormals[k],
                                 b + CubePos[k][2], CubeNormals[k],
                                 b + CubePos[k][3], CubeNormals[k] );

                // Update faces optimized out
                hidden++;
            }
        }

        // Was the cube fully optimized out?
        if ( hidden == 6 ) { hiddenCubes++; }
        
        hiddenFaces += hidden;
    }

    std::cout << " ----- Chunk Statistics ---------------" << std::endl;
    std::cout << "  Cubes: "   << m_cubes.size() << " ("
              << hiddenCubes   << " hidden)"     << std::endl;
    std::cout << "  Sides: "   << totalFaces     << " ("
              << hiddenFaces   << " hidden, " << ( totalFaces-hiddenFaces )
              << " total)"     << std::endl;
    std::cout << "  Verts: "   << builder.numVerts()
              << ", Indices: " << builder.numIndices() << std::endl;

    return builder.createMesh();
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
