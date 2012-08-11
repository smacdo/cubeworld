#ifndef SCOTT_COMMON_GAME_ENTITY
#define SCOTT_COMMON_GAME_ENTITY

#include "entity/entitymanager.h"

/// Uniquely identify an entity within a manager
typedef unsigned int EntityId;

// Forward declarations
class EntityManager;

/**
 * An entity is a unique managed object that contains zero or more components
 * of data.
 */
class Entity
{
public:
    // Entity constructor
    Entity( EntityManager& manager, EntityId id );

    /**
     * Adds an instanced component to the entity.
     */
    template<typename T>
    void add( const T& instance )
    {
        T * pInstance = new T( instance );
        mEntityManager.addComponent( mEntityId, pInstance, T::CID );
    }

    /**
     * Check if the entity contains a given component type
     */
    template<typename T>
    bool has() const
    {
        return mEntityManager.hasComponent( mEntityId, T::CID );   
    }

    /**
     * Retrieves a component attached to this entity. This will trigger
     * an assertion if the entity does not have the requested component
     */
    template<typename T>
    T get()
    {
        return mEntityManager.getComponent<T>( mEntityId );
    }

    /**
     * Deletes a component attached to this enttiy
     */
    template<typename T>
    void remove()
    {
        return mEntityManager.deleteComponent( mEntityId, T::CID );
    }

    EntityId id() const;

    bool operator == ( const Entity& e ) const;
    bool operator != ( const Entity& e ) const;

private:
    /// The factory that manages this entity
    EntityManager& mEntityManager;

    /// Id of this entity
    EntityId mEntityId;
};

#endif
