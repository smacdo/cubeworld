#ifndef SCOTT_MATH_GEOMS_H
#define SCOTT_MATH_GEOMS_H

#include "math/vector.h"
#include <limits>

struct Ray;

struct IntersectResult
{
    IntersectResult()
        : point(Vec3(  0.0f, 0.0f, 0.0f )),
          normal(Vec3( 0.0f, 0.0f, 0.0f )),
          distance( std::numeric_limits<float>::infinity() )
    {
    }

    IntersectResult( const Vec3& pt, const Vec3& n, float dist )
        : point( pt ),
          normal( n ),
          distance( dist )
    {
    }

    bool didHit() const
    {
        return distance != std::numeric_limits<float>::infinity();
    }

    Vec3 point;
    Vec3 normal;
    float distance;
};

/**
 * A single sided plane.
 */
struct Plane
{
    Plane( const Vec3& normal, const Scalar& distance )
        : normal( normal ),
          distance( distance )
    {
    }

    Plane( const Scalar& nX, const Scalar& nY, const Scalar& nZ,
           const Scalar& distance )
        : normal( Vec3( nX, nY, nZ ) ),
          distance( distance )
    {
    }

    void intersects( const Ray& ray )
    {
        float d2 = dot( normal, ray.direction );

        if ( d2 > -ZERO_DELTA )
        {
            return;     // ray is parallel to plane, or ray hits wrong side
        }

        float d1 = -( dot( normal, ray.origin ) + distance );
        float  t = d1 / d2;
        
        if ( t < ZERO_DELTA )
        {
            return;     // ray intersects behind plane origin
        }

        Vec3 intersectPt = ray.origin + ray.direction * t;
    }

    Vec3   normal;
    float  distance;
};

struct Ray
{
    Ray( const Vec3& origin, const Vec3& direction )
        : origin( origin ),
          direction( direction )
    {
    }

    Vec3   origin;
    Vec3   direction;
};

struct Sphere
{
    Sphere( const Vec3& center, const Scalar& radius )
        : center( center ),
          radius( radius )
    {
    }

    Sphere( const Scalar& x, const Scalar& y, const Scalar& z,
            const Scalar& radius )
        : center( Vec3( x, y, z ) ),
          radius( radius )
    {
    }

    Vec3   center;
    Scalar radius;
};

#endif
