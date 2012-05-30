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
#ifndef SCOTT_COMMON_GEOM_INTERSECTION_H
#define SCOTT_COMMON_GEOM_INTERSECTION_H

#include <math/config.h>
#include <math/vector.h>

struct IntersectResult
{
    /**
     * Default constructor. When constructed, sets the intersectresult
     * to be 'infinite', which states that there was no intersection
     */
    IntersectResult();

    /**
     * Constructor. Creates an intersection result
     */
    IntersectResult( const Vec3& pt, const Vec3& n, float dist );

    /**
     * Checks if this intersection result actually resulted in an
     * inteersection
     */
    bool didHit() const;

    /**
     * Point at which the intersection occurred. This value is not valid if
     * no intersection occurred.
     */
    Vec3 point;

    /**
     * Vector specifying the normal to the point of intersection. The normal
     * will point in the same direction as the normal of the intersecting
     * geometry. This value is not valid if no intersection occurred.
     */
    Vec3 normal;

    /**
     * Distance from the ray origin to the point of intersection. This value is
     * not valid if no inteersction occurred.
     */
    float distance;
};

#endif
