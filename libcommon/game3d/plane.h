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
#ifndef SCOTT_COMMON_GEOM_PLANE_H
#define SCOTT_COMMON_GEOM_PLANE_H

#include <math/config.h>
#include <math/vector.h>

struct IntersectResult;
class Ray;
struct BoundingBox;

/**
 * Represents a single sided plane in 3d space
 */
class Plane
{
public:
    // Default constructor
    Plane();

    // Constructor
    Plane( const Vec3& normal, const scalar_t& distance );

    // Constructor
    Plane( const scalar_t& nX,
           const scalar_t& nY,
           const scalar_t& nZ,
           const scalar_t& distance );

    // Constructor
    Plane( const Vec3& ptA,
           const Vec3& ptB,
           const Vec3& ptC );

    // Comparison operator
    bool operator == ( const Plane& p ) const;

    // Calculate distance from the point to this plane
    float distanceToPoint( const Vec3& pt ) const;

    // Check if the ray intersects this planee
    bool intersects( const Ray& ray, Vec3 * pOutIntersection = NULL ) const;

    // Check if a plane intersects this plane
    bool intersects( const Plane& plane ) const;

    /**
     * Returns a vector containing the plane's normal
     */
    inline Vec3 normal() const { return mNormal; }

    /**
     * Distance between the origin and the normal vector
     */
    inline float distance() const { return mDistance; }

private:
    /// Normal vector that defines the plane in 3d space
    Vec3   mNormal;

    /// Distance between the origin and the normal vector
    float  mDistance;
};

#endif
