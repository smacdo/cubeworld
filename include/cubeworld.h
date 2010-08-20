#ifndef SCOTT_ROGUELIKE_CUBEWORLD_H
#define SCOTT_ROGUELIKE_CUBEWORLD_H

#include "point.h"
#include "math/vector.h"
#include <vector>
#include <iosfwd>

namespace Rogue
{

class CubeData;
class WorldCube;
class WorldChunk;
class World;

struct CubeVisitor
{
public:
    virtual void process( const WorldCube& cube ) = 0;
};


/**
 * WorldCube is the "publically visible" portion of the cube to the
 * rest of the game engine. Normally when the world stores the cube in
 * memory, it does lots of fancy tricks to minimize memory use. It also
 * doesn't store its position (position is implicit).
 *
 * However, when handing the data over to the rest of the game for use
 * the engine must make this data available. This class holds both
 * positional data for a cube, as well as containing a pointer to the
 * cube's internal data. You can either access this data directly
 * (probably not recommended), or use you can use helper methods here to
 * access the data.
 *
 */
class WorldCube
{
public:
    /**
     * Default constructor. Specifies a positioned cube that has no
     * associated data (eg, it is "air" or "void").
     *
     * TODO This really should either a) be removed (it doesn't make sense
     * to add "empty" cubes), or b) be changed to have a default of air
     */
    WorldCube( const Point& position )
        : m_data(NULL),
          m_position(position)
    {
    }

    /**
     * TODO same as above
     */
    WorldCube( int x, int y, int z )
        : m_data(NULL),
          m_position( Point( x, y, z ) )
    {
    }

    /**
     * Constructor that specifies a cube's position and associated data
     */
    WorldCube( const Point& position, CubeData* data )
        : m_data(data),
          m_position(position)
    {
    }

    /**
     * Copy constructor
     */
    WorldCube( const WorldCube& cube )
        : m_data(cube.m_data),
          m_position(cube.m_position)
    {
    }

    /**
     * Smart pointer semantics - allows access to cube's data
     */
    inline CubeData* operator -> ()
    {
        return m_data;
    }

    inline const CubeData* operator -> () const
    {
        return m_data;
    }

    bool hasData() const
    {
        // TODO we should return a default <NULLDATA> instead of null check
        return m_data != NULL;
    }

    bool operator == ( const WorldCube& cube ) const
    {
        return m_data == cube.m_data && m_position == cube.m_position;
    }

    friend std::ostream& operator << ( std::ostream& stream, const WorldCube& w );

    Point position() const { return m_position; }

    friend class WorldChunk;

protected:
    // do not delete associated data
    CubeData * m_data;
    Point      m_position;
};

class World
{
public:
    World( int rows, int cols, int depth );
    ~World();

    void put( WorldCube& cube );

    // if cube does not exist, adds it
    WorldCube getAt( int x, int y, int z ) { return getAt(Point(x,y,z)); }
    WorldCube getAt( const Point& position );

    WorldCube firstCubeIntersecting( const Vec3& origin, const Vec3& dir );

    bool isEmptyAt( int x, int y, int z ) { return isEmptyAt(Point(x,y,z)); }
    bool isEmptyAt( const Point& position ) const;

    std::vector<WorldCube> getAllCubes() const;

    void visitAllCubes( CubeVisitor& visitor ) const;

    int rows() const  { return m_rows; }
    int cols() const  { return m_cols; }
    int depth() const { return m_depth; }
    int cubeCount() const;

protected:
    WorldChunk* getChunk( int chunk_r, int chunk_c, int chunk_d );
    WorldChunk* getChunk( int chunk_r, int chunk_C, int chunk_d ) const;

    void makeRelativeToChunk( int& row, int& col, int& depth ) const;
    int getChunkOffsetFor( int chunk_r, int chunk_c, int chunk_d ) const;

    std::vector<WorldChunk*> m_chunks;
    int m_rows;
    int m_cols;
    int m_depth;
};

class WorldChunk
{
public:
    WorldChunk();
    ~WorldChunk();

    void put( WorldCube& cube );

    // if cube does not exist, adds it
    WorldCube getAt( const Point& position );

    bool isEmptyAt( const Point& position ) const;

    WorldCube firstCubeIntersecting( const Vec3& origin, const Vec3& dir );

    std::vector<WorldCube> getAllCubes() const;

    void visitAllCubes( CubeVisitor& visitor ) const;
    int cubeCount() const;

private:

    /**
     * It finds the given world cube's position in the m_cubes
     * array. If the cube cannot be found, it is returned as -1.
     */
    int findCubeOffset( const WorldCube& cube ) const;

    /**
     * It attempts to locate a cube with the given position. If there is
     * no cube at that location, it will return -1.
     */
    int findCubeOffsetByPosition( const Point& position ) const;

    /**
     * Ultra naive way of doing this... but it works!!! (believe it or not)
     */
    std::vector<WorldCube> m_cubes;
};

}

#endif
