#include "entity/tests/components.h"
#include <entity/component.h>
#include "entity/tests/components.h"

const ComponentId Position::CID = 1;
const ComponentId Health::CID   = 2;

Position::Position()
    : x(0), y(0)
{
}

Position::Position( int x_, int y_ )
    : x(x_), y(y_)
{
}

ComponentId Position::cid() const
{
    return CID;
}

bool Position::operator == ( const Position& p ) const
{
    return x == p.x && y == p.y;
}

Health::Health()
    : hp(0)
{
}

Health::Health( int hp_ )
    : hp( hp_ )
{
}

ComponentId Health::cid() const
{
    return CID;
}
