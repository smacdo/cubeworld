#include "cubeworld.h"
#include "cubedata.h"

#include <ostream>

std::ostream& operator << ( std::ostream& stream, const Point& p )
{
    stream << "<" << p.x << ", " << p.y << ", " << p.z << ">";
    return stream;
}

namespace Rogue
{
std::ostream& operator << ( std::ostream& stream, const WorldCube& w )
{
    if ( w.m_data )
    {
        stream << "[worldcube type=" << (int) w.m_data->baseMaterial()
            << ", x=" << w.m_position.x
            << ", y=" << w.m_position.y
            << ", z=" << w.m_position.z
            << "]";
    }
    else
    {
        stream << "[worldcube type=" << "???"
            << ", x=" << w.m_position.x
            << ", y=" << w.m_position.y
            << ", z=" << w.m_position.z
            << "]";
    }

    return stream;
}

}
