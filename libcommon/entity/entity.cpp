#include <entity/entity.h>
#include <common/assert.h>

Entity::Entity( EntityManager& manager, EntityId id )
    : mEntityManager( manager ),
      mEntityId( id )
{
}

EntityId Entity::id() const
{
    return mEntityId;
}

bool Entity::operator == ( const Entity& rhs ) const
{
    // what about different entity managers?
    return mEntityId == mEntityId;
}
