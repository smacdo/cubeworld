#include "math/vector.h"
#include "math/util.h"
#include <cmath>

template<>
float length( const TVector4<float>& v )
{
    return sqrtf( lengthSquared( v ) );
}

template<>
float length( const TVector3<float>& v )
{
    return sqrtf( lengthSquared( v ) );
}

template<>
float length( const TVector2<float>& v )
{
    return sqrtf( lengthSquared( v ) );
}

template<>
float angleBetween( const TVector3<float>& lhs,
                    const TVector3<float>& rhs )
{
    float a = acosf( dot( lhs, rhs ) / ( length( lhs ) * length( rhs ) ) );
    return a * 180.0f / Math::Pi;
}

template<>
TVector4<float> normalized( const TVector4<float>& v )
{
    float len = length( v );
    ASSERT_MSG( len > 0.0f, "Cannot normalize vector of length zero" );

    // If the vector is already normalizd (length is one), then simply return
    // the vector without renormalizing it
    if ( Math::equalsClose( len, 1.0f ) )
    {
        return TVector4<float>( v.mX, v.mY, v.mZ, v.mW );
    }
    else
    {
        return TVector4<float>( v.mX / len, v.mY / len, v.mZ / len, v.mW / len );
    }
}

template<>
TVector3<float> normalized( const TVector3<float>& v )
{
    float len = length( v );
    ASSERT_MSG( len > 0.0f, "Cannot normalize vector of length zero" );

    // If the vector is already normalizd (length is one), then simply return
    // the vector without renormalizing it
    if ( Math::equalsClose( len, 1.0f ) )
    {
        return TVector3<float>( v.mX, v.mY, v.mZ );
    }
    else
    {
        return TVector3<float>( v.mX / len, v.mY / len, v.mZ / len );
    }
}

template<>
TVector2<float> normalized( const TVector2<float>& v )
{
    float len = length( v );
    ASSERT_MSG( len > 0.0f, "Cannot normalize vector of length zero" );

    // If the vector is already normalizd (length is one), then simply return
    // the vector without renormalizing it
    if ( Math::equalsClose( len, 1.0f ) )
    {
        return TVector2<float>( v.mX, v.mY );
    }
    else
    {
        return TVector2<float>( v.mX / len, v.mY / len );
    }
}

template<>
TVector3<float> rotateAroundX( const TVector3<float>& v, float angle )
{
    if ( Math::notZero( angle ) )
    {
        float sangle = sinf( Math::Pi * angle / 180.0f );
        float cangle = cosf( Math::Pi * angle / 180.0f );

        return TVector3<float>( v.mX,
                                v.mY * cangle - v.mZ * sangle,
                                v.mY * sangle + v.mZ * cangle );
    }
    else
    {
        return v;
    }
}

template<>
TVector3<float> rotateAroundY( const TVector3<float>& v, float angle )
{
    if ( Math::notZero( angle ) )
    {
        float sangle = sinf( Math::Pi * angle / 180.0f );
        float cangle = cosf( Math::Pi * angle / 180.0f );

        return TVector3<float>( v.mX * cangle + v.mZ * sangle,
                                v.mY,
                               -v.mX * sangle + v.mZ * cangle );
    }
    else
    {
        return v;
    }
}

template<>
TVector3<float> rotateAroundZ( const TVector3<float>& v, float angle )
{
    if ( Math::notZero( angle ) )
    {
        float sangle = sinf( Math::Pi * angle / 180.0f );
        float cangle = cosf( Math::Pi * angle / 180.0f );

        return TVector3<float>( v.mX * cangle - v.mY * sangle,
                                v.mY * sangle + v.mY * cangle,
                                v.mZ );
    }
    else
    {
        return v;
    }
}

template<>
TVector3<float> rotateAround( const TVector3<float>& v,
                              const TVector3<float>& axis,
                              float angle )
{
    if ( Math::notZero( angle ) )
    {
        float sangle = sinf( Math::Pi * angle / 180.0f );
        float cangle = cosf( Math::Pi * angle / 180.0f );
        float xangle = 1.0f - cangle;    // "1 minus cos angle"

        TVector3<float> u  = normalized( axis );
        TVector3<float> r1( u.mX * u.mX + cangle * ( 1.0f - u.mX * u.mX ),
                            u.mX * u.mY * xangle - sangle * u.mZ,
                            u.mY * u.mZ * xangle + sangle * u.mY );
        TVector3<float> r2( u.mX * u.mY * xangle + sangle * u.mZ,
                            u.mY * u.mY + cangle * ( 1.0f - u.mY * u.mY ),
                            u.mY * u.mZ * xangle - sangle * u.mX );
        TVector3<float> r3( u.mX * u.mZ * xangle - sangle * u.mY,
                            u.mY * u.mZ * xangle + sangle * u.mX,
                            u.mZ * u.mZ + cangle * ( 1.0f - u.mZ * u.mZ ) );

        return TVector3<float>( dot( v, r1 ),
                                dot( v, r2 ),
                                dot( v, r3 ) );
    }
    else
    {
        return v;
    }
}

