#ifndef SCOTT_MATHDEFS_H
#define SCOTT_MATHDEFS_H

#include <limits>

#ifndef MATH_SCALAR_DEFINED
#define MATH_SCALAR_DEFINED
typedef float Scalar;
#endif

#ifndef MATH_DEBUG_MODE
#define MATH_DEBUG_MODE 1
#endif

#define MATH_USE_FUZZY_EQUALS 1
#define MATHLIB_TEMPLATE_CODEGEN

//#if defined(NDEBUG) or defined(_DEBUG) or defined(DEBUG)
#define math_assert(x) assert(x)
//#else
//#define math_assert(x)
//#endif

///////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////
#ifndef PI
#define PI 3.141592653589793238462f
#endif

#ifndef PI2
#define PI2 2.0f * PI
#endif

#ifndef HALF_PI
#define HALF_PI 0.5f * PI
#endif

#ifndef ONEFOURTH_PI
#define ONEFOURTH_PI 0.25f * PI
#endif

#ifndef E
#define E 2.71828182845904523536f
#endif

#ifndef SQRT_TWO
#define SQRT_TWO 1.41421356237309504880f
#endif

#ifndef SQRT_THREE
#define SQRT_THREE 1.73205080756887729352f
#endif

#ifndef SQRT_ONEHALF
#define SQRT_ONEHALF 0.70710678118654752440f
#endif

#ifndef SQRT_ONETHIRD
#define SQRT_ONETHIRD 0.57735026918962576450f
#endif

#ifndef M_DEG2RAD
#define M_DEG2RAD PI / 180.0f
#endif

#ifndef M_RAD2DEG
#define M_RAD2DEG 180.0f / PI
#endif

#ifndef M_SEC2MS
#define M_SEC2MS 1000.0f
#endif

#ifndef M_MS2SEC
#define M_MS2SEC 0.001f
#endif

///////////////////////////////////////////////////////////////////////////
// Angle conversion macros
///////////////////////////////////////////////////////////////////////////
#define DEG2RAD(x) PI*(x)/180
#define RAD2DEG(x) (x)*180/PI

///////////////////////////////////////////////////////////////////////////
// Time conversion macros
///////////////////////////////////////////////////////////////////////////
#define SEC2MS(x) ((x)*1000.f)
#define MS2SEC(x) ((x)*0.001f)

///////////////////////////////////////////////////////////////////////////
// Zero delta and fuzzy zero equals for floating point values
///////////////////////////////////////////////////////////////////////////
#define ZERO_DELTA 0.0000001

#define FUZZY_EQUALS(a,b) ((a) <= ((b)+ZERO_DELTA) && (a) >= ((b)-ZERO_DELTA))
#define IS_ZERO(x) ((a) <= ZERO_DELTA && (a) >= -ZERO_DELTA)

///////////////////////////////////////////////////////////////////////////
// Inline math utility methods
///////////////////////////////////////////////////////////////////////////
template<typename T>
inline T square( const T& x )
{
    return x * x;
}

template<typename T>
inline T cube( const T& x )
{
    return x * x * x;
}

template<typename T, typename U>
U castAndClamp( const T& base )
{
    if ( base > std::numeric_limits<U>::max() )
    {
        return std::numeric_limits<U>::max();
    }
    else if ( base < std::numeric_limits<U>::min() )
    {
        return std::numeric_limits<U>::min();
    }
    else
    {
        return static_cast<U>( base );
    }
}

template<typename T>
T normalizeAngle360( T angle )
{
    if ( angle >= 360.0 || angle < 0.0 )
    {
        angle -= floor( angle / 360.0 ) * 360.0;
    }

    return angle;
}

#ifdef MATHLIB_TEMPLATE_CODEGEN
/* it doesn't make sense to extern template inline funcs!
extern template short     square( short );
extern template int       square( int );
extern template long      square( long );
extern template long long square( long long );
extern template float     square( float );
extern template double    square( double );

extern template short     cube( short );
extern template int       cube( int );
extern template long      cube( long );
extern template long long cube( long long );
extern template float     cube( float );
extern template double    cube( double );

extern template float     normalizeAngle360( float );
extern template double    normalizeAngle360( double );
*/
#endif

#endif
