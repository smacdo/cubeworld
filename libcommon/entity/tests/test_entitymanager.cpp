#include <googletest/googletest.h>
#include <entity/entitymanager.h>
#include <entity/entity.h>
#include "entity/tests/components.h"

class EntityManagerTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        mpManager = new EntityManager( "testmanager" );
    }

    virtual void TearDown()
    {
        delete mpManager;
        mpManager = NULL;
    }

protected:
    EntityManager * mpManager;
};

TEST_F(EntityManagerTests,CreateNewEntity)
{
    Entity e = mpManager->createEntity();
    EXPECT_EQ( 1u, e.id() );
}

TEST_F(EntityManagerTests,CreatingEntitiesGivesNewIds)
{
    Entity a = mpManager->createEntity();
    Entity b = mpManager->createEntity();

    EXPECT_EQ( 1u, a.id() );
    EXPECT_EQ( 2u, b.id() );
}

TEST_F(EntityManagerTests,FindingAnExistingEntity)
{
    Entity a    = mpManager->createEntity();
    EntityId id = a.id();

    // Make sure the entity really exists
    EXPECT_TRUE( mpManager->exists( id ) );

    // Look for it, see if it matches
    Entity b = mpManager->find( id );

    EXPECT_EQ( id, b.id() );
    EXPECT_EQ( a, b );
}

TEST_F(EntityManagerTests,AttachComponentAndRetrieveIt)
{
    Entity e = mpManager->createEntity();
    e.add( Position( 4, 2 ) );

    EXPECT_EQ( Position( 4, 2 ), e.get<Position>() );
}
