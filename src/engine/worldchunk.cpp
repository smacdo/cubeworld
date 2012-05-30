#include "engine/worldchunk.h"
#include "engine/constants.h"
#include "engine/point.h"
#include <vector>
#include <limits>
#include <iostream>

const unsigned int WorldChunk::TOTAL_COLS  = Constants::CHUNK_COLS;
const unsigned int WorldChunk::TOTAL_ROWS  = Constants::CHUNK_ROWS;
const unsigned int WorldChunk::TOTAL_DEPTH = Constants::CHUNK_DEPTH;
const unsigned int WorldChunk::TOTAL_CUBES = Constants::CHUNK_CUBES;

WorldChunk::WorldChunk()
    : mCubes( TOTAL_CUBES )
{
}

WorldChunk::~WorldChunk()
{
}

void WorldChunk::put( const CubeData& cube, const Point& pos )
{
    // Find the location of the cube...
    unsigned int index = findCubeOffset( pos );

    // .. and assign it! So simple
    mCubes[index] = cube;
}

CubeData WorldChunk::at( const Point& pos ) const
{
    return mCubes[ findCubeOffset( pos ) ];
}

bool WorldChunk::isEmptyAt( const Point& pos ) const
{
    unsigned int index = findCubeOffset( pos );
    return mCubes[ index ].isEmpty();
}

std::vector<CubeData> WorldChunk::getAllCubes() const
{
    return std::vector<CubeData>( mCubes );
}

CubeIntersection WorldChunk::firstCubeIntersecting( const Vec3& /*origin*/,
                                                    const Vec3& /*dir*/)
{
    std::vector<WorldCube>::const_iterator itr;

    //
    // Keep track of information about the intersection
    //
    //float minDist  = std::numeric_limits<float>::max();
    CubeIntersection intersection;

    /*
    //
    // Search through all cubes to find any cube that might intersect
    // this ray
    //   (TODO: Look up how to partition space so we don't actually
    //          have to examine each cube)
    //
    Vec3 normal;
    float infinity = std::numeric_limits<float>::infinity();
    float dist     = 0.0f;

    for ( itr = mCubes.begin(); itr != mCubes.end(); ++itr )
    {
        Point p = itr->position();


        //
        // Test if this cube intersects the ray
        //
        dist = intersects( Vec3( static_cast<float>(p[0]),
			                     static_cast<float>(p[1]),
								 static_cast<float>(p[2]) ),
                           Vec3( p[0] + 1.0f, p[1] + 1.0f, p[2] + 1.0f ),
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
    */

    return intersection;
}

unsigned int WorldChunk::cubeCount() const
{
    unsigned int count = 0;

    for ( size_t i = 0; i < mCubes.size(); ++i )
    {
        if (! mCubes[i].isEmpty() )
        {
            count++;
        }
    }

    return count;
}

/**
 * It attempts to locate a cube with the given position. If there is
 * no cube at that location, it will return -1.
 */
unsigned int WorldChunk::findCubeOffset( const Point& pos ) const
{
    // Calculate relative poisition offsets. This could potentially be
    // optimized out
    unsigned int x = pos.x % TOTAL_COLS;
    unsigned int y = pos.y % TOTAL_ROWS;
    unsigned int z = pos.z % TOTAL_DEPTH;

    unsigned int i = ( z * TOTAL_COLS * TOTAL_ROWS ) + 
                       ( y * TOTAL_COLS + x );

    return i;
}
