#ifndef SCOTT_ROGUELIKE_H
#define SCOTT_ROGUELIKE_H

#include "point.h"
#include <vector>
#include <iosfwd>
#include "worldcube.h"          // remove this

namespace Rogue
{

class CubeData;

class WorldCube
{
public:
    WorldCube( const Point& position )
        : m_data(NULL),
          m_position(position)
    {
    }

    WorldCube( int x, int y, int z )
        : m_data(NULL),
          m_position( Point( x, y, z ) )
    {
    }

    WorldCube( const Point& position, CubeData* data )
        : m_data(data),
          m_position(position)
    {
    }

    WorldCube( const WorldCube& cube )
        : m_data(cube.m_data),
          m_position(cube.m_position)
    {
    }

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
    friend class OctreeWorld;

protected:
    // do not delete associated data
    CubeData * m_data;
    Point      m_position;
};

class OctreeWorld
{
public:
    OctreeWorld( int rows, int cols, int depth )
        : m_rows(rows),
          m_cols(cols),
          m_depth(depth)
    {
    }

    ~OctreeWorld()
    {
    }

    void put( WorldCube& cube )
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
    WorldCube getAt( int x, int y, int z )
    {
        WorldCube cube( x, y, z );
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

    bool isEmptyAt( int x, int y, int z ) const
    {
        return isEmptyAt( Point( x, y, z ) );
    }

    bool isEmptyAt( const Point& position ) const
    {
        return findCubeOffsetByPosition( position ) == -1;
    }

    std::vector<WorldCube> getAllCubes() const
    {
        return std::vector<WorldCube>(m_cubes);
    }

    int rows()  const { return m_rows; }
    int cols()  const { return m_cols; }
    int depth() const { return m_depth; }

private:
    int m_rows;
    int m_cols;
    int m_depth;

    CubeData* findCube( const Point& position ) const
    {
        std::vector<WorldCube>::const_iterator itr;
        CubeData * data = NULL;

        for ( itr = m_cubes.begin(); itr != m_cubes.end(); ++itr )
        {
            if ( itr->m_position == position )
            {
                data = itr->m_data;
                break;
            }
        }

        return data;
    }

    /**
     * It finds the given world cube's position in the m_cubes
     * array. If the cube cannot be found, it is returned as -1.
     */
    int findCubeOffset( const WorldCube& cube ) const
    {
        return findCubeOffsetByPosition( cube.m_position );
    }

    /**
     * It attempts to locate a cube with the given position. If there is
     * no cube at that location, it will return -1.
     */
    int findCubeOffsetByPosition( const Point& position ) const
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

    /**
     * Ultra naive way of doing this... but it works!!! (believe it or not)
     */
    std::vector<WorldCube> m_cubes;
};

}

#endif
