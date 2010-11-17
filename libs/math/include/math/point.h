#ifndef SCOTT_ROGUELIKE_POINT_H
#define SCOTT_ROGUELIKE_POINT_H

#include <iostream>     // remove
#include <cassert>
#include "math/mathdefs.h"
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

// X=0, Y=1, Z=2
const int PR[3] = { 1, 2, 0 };  // row
const int PC[3] = { 2, 0, 1 };  // col
const int PD[3] = { 0, 1, 2 };  // depth

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
        : x( static_cast<int>(v[0]) ),
          y( static_cast<int>(v[1]) ),
          z( static_cast<int>(v[2]) )
    {
    }

    Point( size_t axis, int x, int y, int z )
    {
        math_assert( axis < 3 );

        v[PR[axis]] = x;
        v[PC[axis]] = y;
        v[PD[axis]] = z;
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
        math_assert( index < 3 );
        return v[index];
    }

    /**
     * Subscript operator. Allows access to the points three (x/y/z)
     * components.
     */
    int operator[] ( size_t index ) const
    {
        math_assert( index < 3 );
        return v[index];
    }

    /**
     * Checks if all components of the point are equal to zero.
     */
    bool isZero() const
    {
        return ( x == 0 && y == 0 && z == 0 );
    }

    /**
     * Output stream operator
     */
    friend std::ostream& operator << ( std::ostream& s, const Point& p );

protected:
    union 
    {
        struct { int x; int y; int z; };
        int v[3];
    };
};

#endif
