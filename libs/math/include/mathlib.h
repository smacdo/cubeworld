/**
 * Copyright 2010 Scott MacDonald. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *   1. Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Scott MacDonald ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Scott MacDonald OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of Scott MacDonald.
 */
#ifndef SCOTT_MATHLIB_H
#define SCOTT_MATHLIB_H

#include "math/mathdefs.h"
#include "math/vector.h"
#include "math/matrix.h"

/**
 * Checks if two values are pretty close to being equal
 */
//template<typename T>
//inline T fuzzy_equals( const T& a, const T& b )
//{
//    return ( a <= ( b + FUZZY_DELTA) && a >= ( b - FUZZY_DELTA ) );
//}

/**
 * Takes a value, and clamps the value to be in the range [min,max].
 * If it falls out of this range it will be set to the closest value
 * in that range.
 */
template<typename T>
T clamp( const T& v, const T& min, const T& max ) 
{ 
    return ( v < max ? ( v > min ? v : min ) : max );
}

/**
 * Takes two values and returns the minimum value
 */
template<typename T>
T min( const T& a, const T& b )
{
    return ( a < b ? a : b );
}

/**
 * Takes two values, and returns the maximum value
 */
template<typename T>
T max( const T& a, const T& b )
{
    return ( a > b ? a : b );
}

/**
 * Wraps a value to be within the range [0,max]. If the value is
 * larger than max, it will wrap to zero and use the remainder.
 * eg wrap( 34, 32 ) would return 2.
 */
template<typename T>
T wrap( const T& val, const T& max )
{
    assert( val >= 0 && "Value to be wrapped must be positive" );
    return val % max;
}

/**
 * Performs a linear interpolation on the range [x,y] using s as the
 * linear interpolation value.
 */
template<typename T,typename U>
T lerp( const T& x, const T& y, const U& s )
{
    return x + ( ( y - x ) * s);
}

/**
 * Snaps a value to the specified grid size. If the value is not
 * a multiple of grid, then value will be rounded to the nearest multiple
 * of grid.
 */
template<typename T>
T snap( const T& val, const T& grid )
{
    T base = val % grid;
    
    if ( base < ( grid / 2 ) )
    {
        return val - base;
    }
    else
    {
        return ( grid - base ) + val;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Template instantiations - Declare the following common templates extern,
// so the compiler will only expand the templates once
/////////////////////////////////////////////////////////////////////////////
extern template float  min<float>(  const float&,  const float&  );
extern template double min<double>( const double&, const double& );
extern template long   min<long>(   const long&,   const long& );
extern template int    min<int>(    const int&,    const int& );
extern template short  min<short>(  const short&,  const short& );
extern template char   min<char>(   const char&,   const char& );

extern template float  max<float>(  const float&,  const float&  );
extern template double max<double>( const double&, const double& );
extern template long   max<long>(   const long&,   const long& );
extern template int    max<int>(    const int&,    const int& );
extern template short  max<short>(  const short&,  const short& );
extern template char   max<char>(   const char&, const char& );

extern template int    wrap<int>( const int&, const int& );

extern template float  lerp<float>( const float&, const float&, const float& );
extern template float  lerp<float>( const float&, const float&, const double& );
extern template float  lerp<float>( const float&, const float&, const int& );
extern template double lerp<double>( const double&, const double&, const double& );
extern template int    lerp<int>( const int&, const int&, const int& );
extern template Vec3   lerp<Vec3>( const Vec3&, const Vec3&, const float& );
extern template Vec3   lerp<Vec3>( const Vec3&, const Vec3&, const double& );
extern template Vec3   lerp<Vec3>( const Vec3&, const Vec3&, const int& );

extern template int    snap<int>( const int&, const int& );

extern template unsigned long  min<unsigned long>(  const unsigned long&,
                                             const unsigned long& );
extern template unsigned int   min<unsigned int>(   const unsigned int&, 
                                             const unsigned int& );
extern template unsigned short min<unsigned short>( const unsigned short&,
                                             const unsigned short& );
extern template unsigned char  min<unsigned char>(  const unsigned char&,
                                           const unsigned char& );
extern template unsigned long  max<unsigned long>(  const unsigned long&,
                                             const unsigned long& );
extern template unsigned int   max<unsigned int>(   const unsigned int&, 
                                             const unsigned int& );
extern template unsigned short max<unsigned short>( const unsigned short&,
                                             const unsigned short& );
extern template unsigned char  max<unsigned char>(  const unsigned char&,
                                           const unsigned char& );
#endif
