#include "engine/point.h"
#include <ostream>

std::ostream& operator << ( std::ostream& os, const Point& p )
{
    os << "{"
       << "x: " << p.x << ", "
       << "y: " << p.y << ", "
       << "z: " << p.z
       << std::endl;

    return os;
}
