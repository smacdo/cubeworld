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
#ifndef SCOTT_COMMON_GEOM_RAY_H
#define SCOTT_COMMON_GEOM_RAY_H

#include <math/vector.h>
#include <ostream>
#include <string>

/**
 * A ray in 3d space. Has an origin and a normalized direction vector
 */
class Ray
{
public:
    /**
     * Ray constructor. Create a ray from a vector representing the ray's
     * origin and direction
     */
    Ray( const Vec3& origin, const Vec3& direction );

    /**
     * Point where ray originates
     */
    inline Vec3 origin() const { return mOrigin; }

    /**
     * Unit normal vector that specifies the direction of the ray from its
     * origin
     */
    inline Vec3 direction() const { return mDirection; }

private:
    /// Location in 3d sapce in which the ray originates
    Vec3 mOrigin;

    /// Unit normal specifying the direction of the ray from its origin
    Vec3 mDirection;
};

std::ostream& operator << ( std::ostream& os, const Ray& ray );

#endif
