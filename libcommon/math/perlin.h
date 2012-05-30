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

#include <stdlib>

class Random;

/**
 * Random number generator using the mersenne twister algorithm for
 * generating random numbers. This implementation is heavily based on the
 * work of Michael Brundage (which was placed in the public domain).
 */
class PerlinNoise
{
public:
    PerlinNoise( unsigned int seed );
    ~PerlinNoise();

    float noise3( const Vec3& pos ) const;
    float noise3( float x, float y, float z ) const;
    float noise3( float x,
                  float y,
                  float z,
                  int xWrap,
                  int yWrap,
                  int zWrap ) const;

private:
    void init( unsigned int seed );

private:
    /// Size of the random table
    const unsigned int RANDOM_LUT_SIZE = 512;

    /// Buffer of randomly generated values
    unsigned char * mpRandomLUT;
};

#endif
