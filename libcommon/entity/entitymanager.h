#ifndef SCOTT_COMMON_GAME_ENTITY_MANAGER_H
#define SCOTT_COMMON_GAME_ENTITY_MANAGER_H

#include <map>
#include <string>
#include <vector>

#include <common/assert.h>

#include "entity/defs.h"
#include "entity/component.h"

class EntityManager;
class Entity;
class Component;

typedef std::map<EntityId, Component*> EntityComponentMap;
typedef std::map<ComponentId, EntityComponentMap > ComponentStore;

/**
 * Manages the creation, destruction and data components for a set of
 * game entities
 */
class EntityManager
{
public:
    EntityManager( const std::string& name );
    ~EntityManager();

    // Create a new entity
    Entity createEntity();
    
    // See if we have an entity
    bool exists( EntityId entity ) const;

    // Retrieve the entity
    Entity find( EntityId entity );

    EntityId getNextUnusedId();

    // Looks for an entity
    Entity getEntity( const EntityId& id );

    // Add a component
    void addComponent( EntityId entity,
                       Component * pInstance,
                       ComponentId cid );

    // Sets a component on an entity
    void setComponent( EntityId entity,
                       Component * pInstance,
                       ComponentId cid );

    // Returns a copy of the entity's requested component
    template<typename T>
    T getComponent( EntityId entity )
    {
        Component * pComponent = findComponent( entity, T::CID );
        ASSERT_MSG( pComponent != NULL, "Component must exist when retrieving" );

        return T( *reinterpret_cast<T*>( pComponent ) );
    }

    // Deletes a component from an entity
    void deleteComponent( EntityId entity, ComponentId cid );

    // Checks if an entity has the requested component type
    bool hasComponent( EntityId entity, ComponentId cid ) const;

    // Destroys all entities and their components
    void reset();

private:
    // Finds the requested component
    Component* findComponent( ComponentId cid, EntityId eid );

    // Stores the requested component
    void storeComponent( EntityId entity,
                         Component* pInstance,
                         ComponentId cid );

private:
    std::string mManagerName;
    EntityId mNextId;
    ComponentStore mComponentStore;
};

#endif
