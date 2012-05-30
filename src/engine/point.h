#ifndef SCOTT_ROGUELIKE_POINT_H
#define SCOTT_ROGUELIKE_POINT_H

#include <cassert>
#include <ostream>
#include "math/vector.h"

/**
 * This point class is specially designed for our 3d rogue game. It
 * is heavily inspired from Sauerbraten's ivec class.
 *
 * The point class defines a 3d (x,y,z) coordinate space oriented around
 * the given d axis. X is the row, y is the column and z is the coordinate
 * of the reference axis (Z/depth being the default)
 *
 * There is some fun bit tricks in here to make dealing with this really
 * fast, and actually intutitive once you get the hang of things.
 */
class Point
{
public:
    Point()
        : x(0), y(0), z(0)
    {
    }

    Point( int x, int y, int z )
        : x(x), y(y), z(z)
    {
    }

    Point( const Vec3& v )
        : x( static_cast<int>(v.x()) ),
          y( static_cast<int>(v.y()) ),
          z( static_cast<int>(v.z()) )
    {
    }

    /**
     * Copy constructor
     */
    Point( const Point& point )
        : x(point.x), y(point.y), z(point.z)
    {
    }

    /**
     * Assignment operator
     */
    const Point& operator = ( const Point& rhs )
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    /**
     * Equality operator. Since point is integer based, we do not need
     * to compensate for potential floating point equality.
     */
    bool operator == ( const Point& rhs ) const
    {
        return ( x == rhs.x && y == rhs.y && z == rhs.z );
    }

    /**
     * Inequality operator
     */
    bool operator != ( const Point& rhs ) const
    {
        return ( x != rhs.x || y != rhs.y || z != rhs.z );
    }

    /**
     * Addition operator
     */
    Point operator + ( const Point& rhs ) const
    {
        return Point( x + rhs.x,
                      y + rhs.y,
                      z + rhs.z );
    }

    /**
     * Subscript operator. Allows access to the points three (x/y/z)
     * components.
     */
    int& operator[] ( size_t index )
    {
        return v[index];
    }

    /**
     * Subscript operator. Allows access to the points three (x/y/z)
     * components.
     */
    const int& operator[] ( size_t index ) const
    {
        return v[index];
    }

    /**
     * Checks if all components of the point are equal to zero.
     */
    bool isZero() const
    {
        return ( x == 0 && y == 0 && z == 0 );
    }

protected:
    union 
    {
        struct { int x; int y; int z; };
        int v[3];
    };
};

std::ostream& operator << ( std::ostream& os, const Point& p );

#endif
