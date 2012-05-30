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
#ifndef SCOTT_MATH_RANDOM_H
#define SCOTT_MATH_RANDOM_H

#include <stdlib>

/**
 * Random number generator using the mersenne twister algorithm for
 * generating random numbers. This implementation is heavily based on the
 * work of Michael Brundage (which was placed in the public domain).
 */
class RandomGenerator
{
public:
    void init()
    {
        for ( size_t i = 0; i < MT_LEN; ++i )
        {
            m_buffer[i] = rand();
        }

        m_index = 0;
    }

    unsigned long mt_random()
    {
        unsigned long * bp = m_buffer;
        unsigned long    s = 0;
        size_t index       = m_index;
        size_t i           = 0;

        if ( index == MT_LEN * sizeof(unsigned long) )
        {
            index = 0;
            i     = 0;

            for ( ; i < MT_IB; ++i )
            {
                s    = twist( b, i, i+1 );
                b[i] = b[i + MT_IA] ^ (s >> 1) ^ magic(s);
            }

            for ( ; i < MT_LEN-1; ++i )
            {
                s    = twist( b, i, i+1 );
                b[i] = b[i - MT_IB] ^ (s >> 1) ^ magic(s);
            }

            s = twist( b, MT_LEN-1, 0 );
            b[MT_LEN-1] = b[MT_IA-1] ^ (s >> 1) ^ magic(s);
        }

        m_index = index + sizeof(unsigned long);

        return *(unsigned_long *)((unsigned char *)b + index);
    }

private:
    inline unsigned long twist( unsigned int b,
                                unsigned int i,
                                unsigned int j )
    {
        return ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK);
    }

    inline unsigned long magic( unsigned int s )
    {
        return (((s) & 1) * MATRIX_A );
    }

private:
    static const unsigned long MT_LEN = 624;
    static const unsigned long MT_IA  = 397;
    static const unsigned long MT_IB  = 227;    // MT_LEN - MT_IA
    static const unsigned long UPPER_MASK = 0x80000000;
    static const unsigned long LOWER_MASK = 0x7FFFFFFF;
    static const unsigned long MATRIX_A   = 0x9908B0DF;

    size_t m_index;
    unsigned long m_buffer[MT_LEN];
};

/**
 * Generates a random integer and returns it. Completly at the whim
 * of the standard library's random number generator
 *
 * TODO Don't use the built in standard library. Be more creative
 */
template<typename T>
T random()
{
    return static_cast<T>( rand() );
}

/**
 * Generates a random floating point number between 0 and 1
 * TODO: Verify range. Does it include or exclude boundry?
 */
template<>
float random<float>()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/**
 * Generates a random double precision number between 0 and 1
 * TODO: Verify ranges. Does it include or exlude boundry?
 */
template<>
double random<double>()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

/**
 * Returns a random number in the range [min,max]
 */
int random( int min, int max )
{
    return min + ( random<int>() % (max - min + 1) );
}


#endif
