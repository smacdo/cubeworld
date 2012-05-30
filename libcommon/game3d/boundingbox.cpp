#include "game3d/boundingbox.h"
#include "game3d/sphere.h"

/**
 * Axis aligned bounding box constructor. Takes two points, the first of which
 * represents the smallest axis aligned point, and the second is the largest
 * axis aligned point.
 */
BoundingBox::BoundingBox( const Vec3& minPt, const Vec3& maxPt )
    : minPoint( minPt ),
      maxPoint( maxPt )
{
}

/**
 * Checks if the sphere intersects this bounding box, including in the
 * case where the sphere only touches the box
 */
bool BoundingBox::intersects( const Sphere& sphere ) const
{
    float sr = sphere.radius();
    float sx = sphere.center().x();
    float sy = sphere.center().y();
    float sz = sphere.center().z();

    return ( sx - sr < maxPoint.x() ) && ( sx + sr > minPoint.x() ) &&
           ( sy - sr < maxPoint.y() ) && ( sy + sr > minPoint.y() ) &&
           ( sz - sr < maxPoint.z() ) && ( sz + sr > minPoint.z() );
}

/**
 * Checks if the boxes intersect, but not if they touch
 */
bool BoundingBox::intersects( const BoundingBox& other ) const
{
    return 
        ( minPoint.x() < other.maxPoint.x() && maxPoint.x() > other.minPoint.x() &&
          minPoint.y() < other.maxPoint.y() && maxPoint.y() > other.minPoint.y() &&
          minPoint.z() < other.maxPoint.z() && maxPoint.z() > other.minPoint.z() );
}
