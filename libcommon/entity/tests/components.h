#ifndef SCOTT_COMMON_ENTITY_TESTS_COMPONENTS_H
#define SCOTT_COMMON_ENTITY_TESTS_COMPONENTS_H

#include <entity/component.h>

class Position : public Component
{
public:
    Position();
    Position( int x_, int y_ );

    bool operator == ( const Position& p ) const;

    virtual ComponentId cid() const;

    const static ComponentId CID;
    int x, y;
};

class Health : public Component
{
public:
    Health();
    Health( int hp );

    virtual ComponentId cid() const;

    const static ComponentId CID;
    int hp;
};

#endif
