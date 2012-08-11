/*
 * Copyright 2010-2012 Scott MacDonald
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
#ifndef SCOTT_MATH_UTIL_H
#define SCOTT_MATH_UTIL_H

#include <cstdlib>
#include <cmath>
#include <limits>

#include <math/constants.h>

namespace Math
{
    /**
     * Checks if two numeric values of the same type have identical values.
     * For imprecise floating point values, this method will check if they
     * are within an acceptable distance of being equal to each other. 
     *
     * \param  a  Left hand value to compare
     * \param  b  Right nad value to compare
     * \return    True if they are of similiar value (within error tolerance)
     */
    template<typename T>
    inline bool equalsClose( T a, T b )
    {
        return a == b;
    }

    /**
     * Checks if the two single precision floating point values are within
     * an acceptable distance of each other.
     *
     * \param  a  Left hand value to compare
     * \param  b  Right hand value to compare
     * \return    True if they are of similiar value (within error tolerance)
     */
    template<>
    inline bool equalsClose<float>( float a, float b )
    {
        return ( std::fabs( a - b ) < ZeroEpsilonF );
    }

    /**
     * Checks if the two double precision floating point values are within
     * an acceptable distance of each other
     *
     * \param  a  Left hand value to compare
     * \param  b  Right hand value to compare
     * \return    True if they are of similiar value (within error tolerance)
     */
    template<>
    inline bool equalsClose<double>( double a, double b )
    {
        return ( std::fabs( a - b ) < ZeroEpsilonD );
    }

    /**
     * Checks if the value is zero. In the case of floating point values,
     * this method will check if the value is precisely zero or within an
     * acceptable distance (epsilon) of zero.
     *
     * \param  a  Value to check
     * \return    True if the value is within error tolerance of zero
     */
    template<typename T>
    inline bool isZero( T a )
    {
        return ( a == 0 );
    }

    /**
     * Checks if the single precision floating point value is zero or
     * within an acceptable distance of zero.
     *
     * \param  a  Value to check
     * \return    True if the value is within error tolerance of zero
     */
    template<>
    inline bool isZero<float>( float a )
    {
        return ( std::fabs( a ) < ZeroEpsilonF );
    }

    /**
     * Checks if the double precision floating point value is zero or
     * within an acceptable distance of zero
     *
     * \param  a  Value to check
     * \return    True if the value is within error tolerance of zero
     */
    template<>
    inline bool isZero<double>( double a )
    {
        return ( std::fabs( a ) < ZeroEpsilonD );
    }

    /**
     * Checks if value is not zero. Floating point values are checked
     * for near equality
     *
     * \param  a  Value to check
     * \return    True if the value is not within error tolerance of zero
     */
    template<typename T>
    inline bool notZero( T a )
    {
        return ( a != 0 );
    }

    /**
     * Checks if single precision floating point value is not zero
     *
     * \param  a  Value to check
     * \return    True if the value is not within error tolerance of zero
     */
    template<>
    inline bool notZero<float>( float a )
    {
        return std::fabs( a ) > ZeroEpsilonF;
    }

    /**
     * Checks if double precision floating point value is not zero
     *
     * \param  a  Value to check
     * \return    True if the value is not within error tolerance of zero
     */
    template<>
    inline bool notZero<double>( double a )
    {
        return std::fabs( a ) > ZeroEpsilonD;
    }

    /**
     * Return the fractional portion of a value
     *
     * \param  a  Value to extract fraction from
     * \return    Fractional portion of input value
     */
    template<typename T>
    inline T fraction( T /*a*/ )
    {
        return static_cast<T>( 0 );
    }

    /**
     * Return the fractional portion of a value
     *
     * \param  a  Value to extract fraction from
     * \return    Fractional portion of input value
     */
    template<>
    inline float fraction( float a )
    {
        return a - std::floor( a );
    }

    /**
     * Return the fractional portion of a value
     *
     * \param  a  Value to extract fraction from
     * \return    Fractional portion of input value
     */
    template<>
    inline double fraction( double a )
    {
        return a - std::floor( a );
    }

    /**
     * Takes a value, and clamps the value to be in the range [min,max].
     * If it falls out of this range it will be set to the closest value
     * in that range.
     *
     * \param  v    Value to clamp
     * \param  min  Minimum value for clamp range
     * \param  max  Maximal value for clamp range
     * \return      A value that is clamped to the range [min,max].
     */
    template<typename T>
    T clamp( const T& v, const T& min, const T& max ) 
    { 
        return ( v < max ? ( v > min ? v : min ) : max );
    }

    /**
     * Wraps a value to be within the range [0,max]. If the value is
     * larger than max, it will wrap to zero and use the remainder.
     * eg wrap( 34, 32 ) would return 2.
     *
     * \param  val  The value to wrap
     * \param  max  The maximal value before wrapping occurs
     */
    template<typename T>
    T wrap( const T& val, const T& max )
    {
        MATH_ASSERT( val >= 0, "Value to be wrapped must be positive" );
        return val % max;
    }

    /**
     * Snaps a value to the specified grid size. If the value is not
     * a multiple of grid, then value will be rounded to the nearest multiple
     * of grid.
     *
     * \param  val   The value to snap
     * \param  grid  Snap value to use
     * \return       The input value, snapped to a multiple of grid
     */
    template<typename T>
    T snap( const T& val, const T& grid )
    {
        T base = val % grid;

        // Account for negatives
        if ( base < 0 )
        {
            base += grid;
        }
        
        if ( base < ( grid / 2 ) )
        {
            return val - base;
        }
        else
        {
            return ( grid - base ) + val;
        }
    }

    /**
     * Returns the passed value squared (x*x)
     *
     * \param  x  Value to square
     * \return    The value squared
     */
    template<typename T>
    inline T square( const T& x )
    {
        return x * x;
    }

    /**
     * Returns the passed value cubed (x*x*x)
     *
     * \param  x  Value to cube
     * \return    The value cubed
     */
    template<typename T>
    inline T cube( const T& x )
    {
        return x * x * x;
    }

    /**
     * Clamps an angle given in degrees to its natural 0-360 range.
     *
     * \param  angle  Value of the angle to clamp
     * \return        The angle with it's value clamped to [0,360]
     */
    template<typename T>
    inline T clampAngle( T angle )
    {
        angle = angle % 360;

        if ( angle < 0 )
        {
            angle += 360;
        }

        return angle;
    }

    /**
     * Returns a clamped double precision angle in [0, 360.0]
     *
     * \param  angle  Value of the angle to clamp
     * \return        The angle with it's value clamped to [0,360]
     */
    template<>
    inline double clampAngle<double>( double angle )
    {
        angle = std::fmod( angle, 360.0 );

        if ( angle < 0.0 )
        {
            angle += 360.0;
        }

        return angle;
    }

    /**
     * Returns clamped single precision angle in [0, 360.0]
     *
     * \param  angle  Value of the angle to clamp
     * \return        The angle with it's value clamped to [0,360]
     */
    template<>
    inline float clampAngle<float>( float angle )
    {
        angle = std::fmod( angle, 360.0f );
        
        if ( angle < 0.0f )
        {
            angle += 360.0f;
        }

        return angle;
    }

    /**
     * Returns the next highest power of two value for the given
     * argument v.
     *
     * \param  n  Value to use when searching for next power of two
     * \return    The next power of two
     */
    template<typename T>
    T nextPowerOfTwo( T n )
    {
        static_assert( std::numeric_limits<T>::is_integer, "Cannot be float" );

        std::size_t k = 1;
        n -= 1;

        do
        {
            n  |= n >> k;
            k <<= 1;
        }
        while ( k < static_cast<size_t>(std::numeric_limits<T>::digits) );

        return ++n;
    }

    /**
     * Returns the next highest power of two value for the given
     * argument v.
     *
     * \param  n  Value to use when searching for next power of two
     * \return    The next power of two
     */
    template<>
    inline unsigned int nextPowerOfTwo( unsigned int v )
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;

        return v;
    }

    /**
     * Computes a 32 bit hash from a floating point value. This is used to
     * quickly cache floats into a hashmap, but care must be taken since two
     * seemingly identical floating point values can have different memory values
     * and hence different hash values
     *
     * \param  value  Floating point value to hash
     * \return        Numeric hash code
     */
    inline unsigned int hashfloat( float value );

    /**
     * Computes a 32 bit hash from a floating point value. This is used to
     * quickly cache floats into a hashmap, but care must be taken since two
     * seemingly identical floating point values can have different memory values
     * and hence different hash values
     *
     * \param  pArray     Pointer to an array of floating point values
     * \param  arraySize  Number of floating point values in array
     * \return            Numeric hash code
     */
    inline unsigned int hashfloat( const float * pArray, size_t arraySize );

    /**
     * Quickly computes the approximate square root of the input value
     */
    float fastSqrt( float f );
}

#endif
