#ifndef SCOTT_CUBEWORLD_CUBECHUNK_H
#define SCOTT_CUBEWORLD_CUBECHUNK_H

#include "math/vector.h"
#include "engine/point.h"
#include "engine/cubeintersection.h"
#include "engine/worldcube.h"
#include <vector>

class CubeData;

/**
 * A "WorldChunk" is a collection of cubes that exist together
 * [NEED MORE DESCRIPTION]
 */
class WorldChunk
{
public:
    WorldChunk();
    ~WorldChunk();

    // Place a cube
    void put( const CubeData& cube, const Point& pos );
    
    // Retrieve a cube
    CubeData at( const Point& position ) const;

    // Check if position is empty (EMPTY cube)
    bool isEmptyAt( const Point& position ) const;

    // Find the first cube that intersects
    CubeIntersection firstCubeIntersecting( const Vec3& origin,
                                            const Vec3& dir );

    // Return a list of all cubes in this chunk
    std::vector<CubeData> getAllCubes() const;

    // Return number of cubes that are populated
    unsigned int cubeCount() const;

    // Return if the cube's view data needs to be regenerated
    bool isRebuildingView() const;

    // Change the view dirty flag
    void setIsRebuildingView( bool isDirty );

public:
    const static unsigned int TOTAL_COLS;
    const static unsigned int TOTAL_ROWS;
    const static unsigned int TOTAL_DEPTH;
    const static unsigned int TOTAL_CUBES;

private:
    // Returns the cube offset for a given (RELATIVE!) position
    unsigned int findCubeOffset( const Point& position ) const;

private:
    // Contains all of the vector's cubes
    std::vector<CubeData> mCubes;

    // Flag specifying if the chunk's view needs to be updated
    bool mIsRebuildingView;
};

#endif
