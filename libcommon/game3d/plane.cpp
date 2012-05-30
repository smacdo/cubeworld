/*
 * Copyright 2010-2012 Scott MacDonald. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY SCOTT MACDONALD ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL SCOTT MACDONALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Scott MacDonald.
 */
#include <game3d/intersection.h>
#include <game3d/plane.h>
#include <game3d/ray.h>
#include <limits>

Plane::Plane( const Vec3& normal, const Scalar& distance )
    : mNormal( normal ),
      mDistance( distance )
{
}

Plane::Plane( const Scalar& nX, const Scalar& nY, const Scalar& nZ,
              const Scalar& distance )
    : mNormal( Vec3( nX, nY, nZ ) ),
      mDistance( distance )
{
}

bool Plane::intersects( const Ray& ray, Vec3 * pOutIntersectionPt ) const
{
    Scalar d2 = dot( mNormal, ray.direction() );

    if ( d2 > -Math::ZeroEpsilonF ) 
    {
        return false;     // ray is parallel to plane, or ray hits wrong side
    }

    Scalar d1 = -( dot( mNormal, ray.origin() ) + mDistance );
    Scalar  t = d1 / d2;
    
    if ( t < Math::ZeroEpsilonF )
    {
        return false;     // ray intersects behind plane origin
    }

    if ( pOutIntersectionPt != NULL )
    {
        *pOutIntersectionPt = ray.origin() + ray.direction() * t;
    }

    return true;
}
