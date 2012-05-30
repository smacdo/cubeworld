
#include <math/util.h>
#include <math/config.h>

/**
 * Computes a 32 bit hash from a floating point value. This is used to
 * quickly cache floats into a hashmap, but care must be taken since two
 * seemingly identical floating point values can have different memory values
 * and hence different hash values
 */
inline unsigned int hashfloat( float value )
{
    const unsigned int *intPtr =
        reinterpret_cast<unsigned int *>( &value );
    return *intPtr;
}

/**
 * Computes an unsigned 32 bit hash value from an array of floating
 * point values.
 */
inline unsigned int hashfloat( const float * pArray, size_t arraySize )
{
    unsigned int hash             = 0u;
    const unsigned int *pIntArray =
        reinterpret_cast<const unsigned int*>( pArray );

    for ( size_t i = 0; i < arraySize; ++i )
    {
        hash ^= pIntArray[i];
    }

    return hash;
}


float Math::fastSqrt( float v )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = v * 0.5f;
    y  = v;
    i  = *( long *) &y;             // evil floating point bit level hack
    i  = 0x5f3759df - ( i >> 1 );   // seriously, wtf
    y  = *( float *) &i;            // more magic
    y  = y * (threehalfs - (x2 * y * y));   // 1st iteration
//  y  = y * (threehalfs - (x2 * y * y));   // 2nd itr, can be removed

    return y;
}
