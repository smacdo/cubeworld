#include <entity/entitymanager.h>
#include <entity/entity.h>
#include <entity/component.h>
#include <common/assert.h>
#include <common/delete.h>
#include <app/logging.h>

#include <iostream>
 
/**
 * Constructor
 */
EntityManager::EntityManager( const std::string& name )
    : mManagerName( name ),
      mNextId( 1 ),
      mComponentStore()
{
}

/**
 * Destructor
 */
EntityManager::~EntityManager()
{
    reset();
}

/**
 * Check if an entity exists
 */

/**
 * Find an entity
 */
Entity EntityManager::find( EntityId id )
{
    
}

/**
 * Delete all of the components and entities from this manager
 */
void EntityManager::reset()
{
    size_t components = 0;
    size_t instances  = 0;

    // Clean up allocated entities and instances
    ComponentStore::iterator itr = mComponentStore.begin();

    for ( ; itr != mComponentStore.end(); ++itr )
    {
        // Traverse each component's list of entites and delete the
        // entity's associated component instance
        EntityComponentMap::iterator inner = itr->second.begin();

        for ( ; inner != itr->second.end(); ++inner )
        {
            Component *pComponent = inner->second;
            Delete( pComponent );

            instances++;
        }

        components++;
    }

    LOG_DEBUG("EntityManager")
        << "Deleted " << instances << " entities with a total of "
        << components << " components";

    // Reset the entity map
    mComponentStore = ComponentStore();
}

/**
 * Create a new entity
 */
Entity EntityManager::createEntity()
{
    return Entity( *this, mNextId++ );
}

/**
 * Returns the next unused entity id
 */
EntityId EntityManager::getNextUnusedId()
{
    return mNextId++;
}

/**
 * Add a component to an entity
 */
void EntityManager::addComponent( EntityId entityId,
                                  Component * pInstance,
                                  ComponentId cid )
{
    ASSERT_MSG( pInstance != NULL, "Cannot add a null component to an entity" );
    ASSERT_MSG( pInstance->cid() == cid, "Component type must match" ); 

    // Make sure the entity doesn't already have this entity associated with
    // it
    ASSERT( hasComponent( entityId, cid ) == false );

    // Now attach the component
    storeComponent( entityId, pInstance, cid );
}

/**
 * Associates a component to the given entity id. If the entity already has
 * a component of this type, it will be deleted prior.
 */
void EntityManager::storeComponent( EntityId entity,
                                    Component * pInstance,
                                    ComponentId cid )
{
    ASSERT_MSG( pInstance != NULL, "Cannot add a null component to an entity" );
    ASSERT_MSG( pInstance->cid() == cid, "Component type must match" ); 

    // Locate the map that contains all of the entities having a
    // component of type T. If this has not been created (itr = null),
    // then make sure to initialize it
    ComponentStore::iterator csItr = mComponentStore.find( cid );

    if ( csItr == mComponentStore.end() )
    {
        mComponentStore[ cid ] = EntityComponentMap();
        csItr                  = mComponentStore.find( cid );
    }

    // Grab the map of entities containing component 'T'. From here,
    // associate the entitiy id to a newly created instance copied from
    // componentInstance
    EntityComponentMap& eCompStore           = csItr->second;
    EntityComponentMap::iterator eCompMapItr = eCompStore.find( entity );

    if ( eCompMapItr != eCompStore.end() )
    {
        // There is an instance of the component stored for this
        // entity. Use the assignment operator to avoid having to delete
        // the object
        Component * pComponent = eCompMapItr->second;
        ASSERT_MSG( cid == pComponent->cid(), "Component type ID must match" );

        Delete( pComponent );
    }
 
    // Assign the component
    eCompStore[ entity ] = pInstance;
}

/**
 * Retrieve a component
 */
Component* EntityManager::findComponent( EntityId entity,
                                         ComponentId cid )
{
    EntityComponentMap& store              = mComponentStore[ cid ];
    EntityComponentMap::const_iterator itr = store.find( entity );
    Component * pComponent                 = NULL;

    if ( itr != store.end() )
    {
        pComponent = itr->second;
    }

    // Return the component to the caller
    return pComponent;
}

void EntityManager::deleteComponent( EntityId entity, ComponentId cid )
{
}

bool EntityManager::hasComponent( EntityId eid, ComponentId cid ) const
{
    ComponentStore::const_iterator itr = mComponentStore.find( cid );
    bool didFind = false;

    if ( itr != mComponentStore.end() )
    {
        didFind = ( itr->second.find(eid) != itr->second.end() );
    }

    return didFind;
}

