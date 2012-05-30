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
#ifndef SCOTT_MATH_INTERPOLATION_H
#define SCOTT_MATH_INTERPOLATION_H

#include <math/util.h>
#include <cmath>

namespace Math
{

    template<typename T, class Func>
    float easeIn( float time )
    {
        return Func::easeIn( time );
    }

    /**
     * Performs a linear interpolation on the range [x,y] using s as the
     * ratio
     *
     * \param  x  Starting value
     * \param  y  Ending value
     * \param  s  Interpolation factor (ranges [0,1])
     * \return    Interpolated value in the range [x,y] biased by s
     */
    template<typename T,typename U>
    T lerp( const T& x, const T& y, const U& s )
    {
        return x + ( ( y - x ) * s);
    }

    /**
     * Smoothstep performs a smoother version of a linear interpolation
     * between two values. This implementation uses an improved version
     * proposed by Ken Perlin
     *
     * \param  x  Starting value
     * \param  y  Ending value
     * \param  s  Interpolation factor [0,1]
     * \return    Interpolated value in the range [x,y] biased by s
     *
     * s(t) = 6t^5 - 15t^4 + 10t^3
     */
    template<typename T, typename U>
    T smoothstep( const T& a, const T& b, const U& s )
    {
        T v = ( s - a ) / ( b - a );
        T x = Math::clamp( v, static_cast<T>(0), static_cast<T>(1) );
        
        return x * x * x * ( x * ( x * 6 - 15 ) + 10 );
    }

    /**
     * Performs a hermite linear interpolation on the range [a,b] using s as
     * the interpolvation percent (0 = a, 1=b). Similiar to a linear
     * interpolation, however the interpolation is eased near the limits of 
     * the range.
     */
    template<typename T, typename U>
    T hermite( const T& a, const T& b, const U& s )
    {
        return lerp( a, b, s * s * ( 3.0f - 2.0f * s ) );
    }

    /**
     * Performs a sinusoidal interpolation on the range [a,b] using s as the
     * interpolation percent (0 = a, 1=b). Similiar to a linear interpolation,
     * however the interpolation is eased near the upper limit of the range.
     */
    template<typename T, typename U>
    T sinerp( const T& a, const T& b, const U& s )
    {
        return lerp( a, b, sin( s * Math::Pi * 0.5f ) );
    }

    /**
     * Performs a cosinusoidal interpolation on the range [a,b] using s as the
     * interpolation percent (0=a, 1=b). Similiar to a linear interpolation,
     * however the interpolation is eased near the lower limit of the range.
     */
    template<typename T, typename U>
    T coserp( const T& a, const T& b, const U& s )
    {
        return lerp( a, b, cos( s * Math::Pi * 0.5f ) );
    }

    /**
     * Performs a "boing!" interpolation on the range [a,b] using s as the
     * interpolation percent (0=a, 1=b). Berp will cause the interpolated
     * value to overshoot the upper limit, waver back and forth before finally
     * converging on the upper limit.
     */
    template<typename T, typename U>
    T berp( const T& /*a*/, const T& /*b*/, const U& s )
    {
        T v = clamp( s, 0, 1 );
        v = sin(v * Math::Pi * (0.2f + 2.5f * s*s*s)) *
            pow(1.0f-s,2.2f);

    // value = Mathf.Clamp01(value);
    // value = (Mathf.Sin(value * Mathf.PI * (0.2f + 2.5f * value * value * value)) * Mathf.Pow(1f - value, 2.2f) + value) * (1f + (1.2f * (1f - value)));
    // return start + (end - start) * value;
        return v;
    }

    /**
     * Performs a bouncing interpolation on the range [a,b] using s as the
     * interpolation percent (0=a, 1=b). The value will exhibit a "bouncing"
     * behavior as it bounces from its lower limit to upper limit before
     * slowly settling on its lower limit as s approaches 1. 
     *
     * Very similiar to OS X's dock
     */
    template<typename T, typename U>
    T bounce( const T& a, const T& b, const U& s )
    {
        U x = fabs(sinf( 6.28f * (s + 1.0f) * (s + 1.0f)) * (1.0f - s) );
        return a + (b-a) * x;
    }
}

#endif
