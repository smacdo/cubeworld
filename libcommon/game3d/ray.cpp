#include "game3d/ray.h"
#include "math/vector.h"

#include <ostream>

Ray::Ray( const Vec3& origin, const Vec3& direction )
    : mOrigin( origin ),
      mDirection( direction )
{
}

std::ostream& operator << ( std::ostream& os, const Ray& r )
{
    os << "{ray: pos=" << r.origin() << ",dir=" << r.direction() << "}";
    return os;
}
