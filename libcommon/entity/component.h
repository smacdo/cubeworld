#ifndef SCOTT_COMMON_GAME_COMPONENT_H
#define SCOTT_COMMON_GAME_COMPONENT_H

#include <entity/defs.h>

/**
 * Component is the base class for all entity components. They are
 * associated to an individual entity, and store information relating to
 * their type.
 *
 * All components must support copy construction and assignment
 */
class Component
{
public:
    virtual ~Component() { };
    virtual ComponentId cid() const = 0;
};

#endif
