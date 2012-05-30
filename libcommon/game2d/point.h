/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SCOTT_COMMON_MATH_POINT_H
#define SCOTT_COMMON_MATH_POINT_H

#include <iosfwd>

// boost serialization forward declaration
namespace boost { namespace serialization { class access; } }

/**
 * Represents a 2d cartesian point using integer values.
 */
class Point
{
public:
    // Default constructor. Sets the point to (0,0)
    Point();

    // Constructor that takes an intial x/y point
    Point( int x, int y );

    // Copy constructor
    Point( const Point& p );

    // Assignment operator
    Point& operator = ( const Point& rhs  );

    // Used for ordering and comparing points. Does not actually mean
    // a point is less than another point... that doesn't really make
    // any sense!
    bool operator < ( const Point& rhs ) const;

    // Used for ordering and comparing points with STL algorithms. This
    // operator should never be used to in the same context as a numerical
    // "this point is less than that point"
    bool operator > ( const Point& rhs ) const;

    // Equality operator
    bool operator == ( const Point& rhs ) const;

    // Inequality operator
    bool operator != ( const Point& rhs ) const;

    // Addition operator
    Point operator + ( const Point& rhs ) const;

    // Subtraction operator
    Point operator - ( const Point& rhs ) const;

    // Negation operator
    Point operator - () const;

    // Self addition operator
    Point& operator += ( const Point& rhs );

    // Self subtraction operator
    Point& operator -= ( const Point& rhs );

    // Return a translated point
    Point translate( int dx, int dy ) const;

    // Check if point is zero
    bool isZero() const;

    // Get x component
    int x() const;

    // Get y component
    int y() const;

    // Set the x and y component of the point class
    void set( int x, int y );

    /////////////////////////
    // Boost serialization //
    /////////////////////////
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize( Archive& ar, const unsigned int /*version*/ )
    {
        ar & mX;
        ar & mY;
    }

private:
    int mX;
    int mY;
};

std::ostream& operator << ( std::ostream& stream, const Point& point );

#endif
