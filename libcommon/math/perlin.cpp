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
#ifndef SCOTT_MATH_PERLIN_H
#define SCOTT_MATH_PERLIN_H

#include <cstdlib>
#include <boost/random.hpp>

namespace
{
    inline float p_ease( float a )
    {
        return ((( a * 6 - 15 ) * a + 10 ) * a * a * a);
    }
}

PerlinNoise::PerlinNoise( unsigned int seed )
    : pRandomLUT( new unsigned char[RANDOM_LUT_SIZE] )
{
    init( seed );
}

PerlinNoise::PerlinNoise( const PerlinNoise& p )
    : pRandomLUT( new unsigned char[RANDOM_LUT_SIZE] )
{
    std::copy( p.pRandomLUT,
               p.pRandomLUT + RANDOM_LUT_SIZE,
               pRandomLut );
}

PerlinNoise::~PerlinNoise()
{
    delete[] pRandomLUT;
}

PerlinNoise& PerlinNoise::operator = ( const PerlinNoise& rhs )
{
    // Only copy the random lookup table if we are not the same instance
    if ( this == &p )
    {
        // Destroy original random buffer
        delete[] pRandomLUT;

        // Now re-create the buffer, and populate it with the contents of
        // 'rhs'
        pRandomLUT = new unsigned char[RANDOM_LUT_SIZE];

        std::copy( rhs.pRandomLUT,
                   rhs.pRandomLUT + RANDOM_LUT_SIZE,
                   pRandomLUT );
    }

    return *this;
}

float PerlinNoise::noise3( const Vec3& pos ) const
{
    return noise3( pos.x(), pos.y(), pos.z(), 0, 0, 0 );
}

float PerlinNoise::noise3( float x, float y, float z ) const
{
    return noise3( x, y, z, 0, 0, 0 );
}

float PerlinNoise::noise3( float x,
                           float y,
                           float z,
                           int xWrap,
                           int yWrap,
                           int zWrap ) const
{
}

float PerlinNoise::grad( int hash, float x, float y, float z )
{
    // Table of pre-computed gradient vectors
    const static float BASIS[12][3] =
    {
        {  1, 1, 0 },
        { -1, 1, 0 },
        {  1,-1, 0 },
        { -1,-1, 0 },
        {  1, 0, 1 },
        { -1, 0, 1 },
        {  1, 0,-1 },
        { -1, 0,-1 },
        {  0, 1, 1 },
        {  0,-1, 1 },
        {  0, 1,-1 },
        {  0,-1,-1 },
    };

    // perlin's gradient has 12 cases so some get used 1/16th of the time
    // and some 2/16ths. We reduce bias by changing those fractions
    // to 5/16ths and 6/16ths, and the same 4 cases get the extra weight.
    const static unsigned char INDICES[64] =
    {
        0, 1, 2, 3,  4, 5, 6, 7, 8, 9, 10, 11,
        0, 9, 1, 11,
        0, 1, 2, 3,  4, 5, 6, 7, 8, 9, 10, 11,
        0, 1, 2, 3,  4, 5, 6, 7, 8, 9, 10, 11,
        0, 1, 2, 3,  4, 5, 6, 7, 8, 9, 10, 11,
        0, 1, 2, 3,  4, 5, 6, 7, 8, 9, 10, 11,
    };

    // Generate the value using the reference permutation table
    float *pGrad = BASIS[ INDICES[ hash & 63 ] ];
    return pGrad[0] * x + pGrad[1] * y + pGrad[2] * z;
}

float PerlinNoise::noise( float x, float y, float z ) const
{
    return noise( x, y, z, 0, 0, 0 );
}

float PerlinNoise::noise( const Vec3& v ) const
{
    return noise( v.x(), v.y(), v.z(), 0, 0, 0 );
}

float PerlinNoise::noise( float x, float y ) const
{

}

float PerlinNoise::noise( float x, float y, float z,
                          int x_wrap,
                          int y_wrap,
                          int z_wrap ) const
{
    float u, v, w;
    float n000, n001, n010, n011, n100, n101, n110, n111;
    float n00, n01, n10, n11;
    float n0, n1;

    unsigned int x_mask = ( x_wrap - 1 ) & 255;
    unsigned int y_mask = ( y_wrap - 1 ) & 255;
    unsigned int z_mask = ( z_wrap - 1 ) & 255;

    // Find the unit cube that contains point. We "cut" the points by
    // forcing our x/y/z values into a [0,*_wrap] range that will become
    // the maximums of our unit cube (x0,y0,z0 --> x1,y1,z1)
    int px = std::floor( x );
    int py = std::floor( y );
    int pz = std::floor( z );

    int x0 = px & x_mask, x1 = (px + 1) & x_mask;
    int y0 = py & y_mask, y1 = (py + 1) & y_mask;
    int z0 = py & z_mask, z1 = (pz + 1) & z_mask;

    int r0, r1, r00, r01, r10, r11;

    // Find the relative X/Y/Z of point in the unit cube by rounding our
    // coordinates to the nearest int
    x -= px;
    y -= py;
    z -= pz;

    // Compute the fade curves for x/y/z
    u  = p_ease( x );
    v  = p_ease( y );
    w  = p_ease( z );

    // Hash coordinates of the eight unit cube corners
    r0 = mpRandomLUT[ x0 ];
    r1 = mpRandomLUT[ x1 ];

    r00 = mpRandomLUT[ r0 + y0 ];
    r01 = mpRandomLUT[ r0 + y1 ];
    r10 = mpRandomLUT[ r1 + y0 ];
    r11 = mpRandomLUT[ r1 + y1 ];

    // Calculate the results from the eight corners of the unit cube,
    // and then blend the results into a single returnable value
    n000 = grad( mpRandomLUT[r00+z0], x  , y  , z   );
    n001 = grad( mpRandomLUT[r00+z1], x  , y  , z-1 );
    n010 = grad( mpRandomLUT[r01+z0], x  , y-1, z   );
    n011 = grad( mpRandomLUT[r01+z1], x  , y-1, z-1 );
    n100 = grad( mpRandomLUT[r10+z0], x-1, y  , z   );
    n101 = grad( mpRandomLUT[r10+z1], x-1, y  , z-1 );
    n110 = grad( mpRandomLUT[r11+z0], x-1, y-1, z   );
    n111 = grad( mpRandomLUT[r11+z1], x-1, y-1, z-1 );

    n00 = lerp( n000, n001, w );
    n01 = lerp( n010, n011, w );
    n10 = lerp( n100, n101, w );
    n11 = lerp( n110, n111, w );

    n0 = lerp( n00, n01, v );
    n1 = lerp( n10, n11, v );

    return lerp( n0, n1, u );
}

float PerlinNoise::lerp( float a, float b, float t )
{
    return a + ( b - a ) * t;
}

void PerlinNoise::init( unsigned int seed )
{
    boost::mt19937 rng( seed );
    boost::uniform_smallint<> randomNumber( 0, 255 );

    // Generate the look up table. Remember that the look up table contains
    // 256 unique elements, but each element is duplicated (at pos i and
    // i+256)
    for ( unsigned int i = 0; i < RANDOM_LUT_SIZE / 2; ++i )
    {
        unsigned char val   = randomNumber( rng );
        pRandomLUT[i + 0]   = val;
        pRandomLUT[i + 256] = val;
    }
}
