/**
 * Copyright 2010 Scott MacDonald. All rights reserved.
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
#include <game3d/frustum.h>
#include <game3d/boundingbox.h>

#include <math/vector.h>

bool Frustum::isInFrustum( const BoundingBox& box ) const
{
    float minX = 0.0, minY = 0.0, minZ = 0.0;
//    float maxX = 0.0, maxY = 0.0, maxZ = 0.0;
    bool bIsInFrustrum = true;

    for ( int i = 0; i < PlaneCount; ++i )
    {
        //
        // Test X/Y/Z axis
        //
        if ( m_planes[i].normal()[0] > 0 )
        {
            minX = box.minPoint[0];
//            maxX = box.maxPoint[0];
        }
        else
        {
            minX = box.maxPoint[0];
//            maxX = box.minPoint[0];
        }

        if ( m_planes[i].normal()[1] > 0 )
        {
            minY = box.minPoint[1];
//            maxY = box.maxPoint[1];
        }
        else
        {
            minY = box.maxPoint[1];
//            maxY = box.minPoint[1];
        }

        if ( m_planes[i].normal()[2] > 0 )
        {
            minZ = box.minPoint[2];
//            maxZ = box.maxPoint[2];
        }
        else
        {
            minZ = box.maxPoint[2];
//            maxZ = box.minPoint[2];
        }

        //
        // Does it intersect the plane? Is it outside the plane?
        //
        Vec3 min( minX, minY, minZ );

        if ( dot( m_planes[i].normal(), min ) + m_planes[i].distance() > 0.0f )
        {
            // It is outside the plane. Hurrah!
            bIsInFrustrum = false;
            break;
        }
//      else if ( dot( m_planes[i].normal, max ) + planes[i].distance >= 0.0f )
//      {
//          // It intersects the plane. Keep testing
//          bIsInFrustrum = true;
//      }
    }

    return bIsInFrustrum;
}
