/*
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
#ifndef SCOTT_COMMON_GEOM_UTILS_H
#define SCOTT_COMMON_GEOM_UTILS_H

#include <math/vector.h>

/**
 * Calculates the surface normal for three coplanar vertex points forming
 * a triangle. The points must be specified in a consistent winding order,
 * otherwise the results of this method are undefined
 *
 * \param  p0  The first vertex forming the triangle
 * \param  p1  The second vertex forming the triangle
 * \param  p3  The third vertex forming the triangle
 * \return The surface normal vector
 */
template<typename T>
TVector3<T> CalculateSurfaceNormal( const TVector3<T>& p0,
                                    const TVector3<T>& p1,
                                    const TVector3<T>& p2 )
{
    TVector3<T> u = p1 - p0;
    TVector3<T> v = p2 - p0;

    return TVector3<T>( u.Y() * v.Z() - u.Z() * v.Y(),
                        u.Z() * v.X() - u.X() * v.Z(),
                        u.X() * v.Y() - u.Y() - v.X() );
}


#endif
