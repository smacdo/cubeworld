#include "gtest.h"
#include "octreeworld.h"
#include "worldcube.h"

using namespace Rogue;

class OWTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        world = new OctreeWorld( 4, 4, 3 );
    }

    virtual void TearDown()
    {
        delete world;
    }

    OctreeWorld * world;
};

/*class OWVisitor : public OctreeWorldVisitor
{
public:
    virtual void operator() ( WorldCube& cube )
    {
    }
};*/

TEST_F(OWTest,NewWorldShouldBeEmpty)
{
    for ( int z = 0; z <world->depth(); ++z )
    {
        for ( int y = 0; y < world->rows(); ++y )
        {
            for ( int x = 0; x < world->cols(); ++x )
            {
                EXPECT_TRUE( world->isEmptyAt( x, y, z ) );
            }
        }
    }
}

TEST_F(OWTest,SettingACubeMakesItNotEmpty)
{
    WorldCube cube( 0, 0, 2);
    EXPECT_TRUE( world->isEmptyAt( 0, 0, 2 ) );

    world->put( cube );
    
    EXPECT_FALSE( world->isEmptyAt( 0, 0, 2 ) );
}

TEST_F(OWTest,GetACubeThatDoesNotExistAddsIt)
{
    EXPECT_TRUE( world->isEmptyAt( 0, 1, 2 ) );

    world->getAt( 0, 1, 2 );

    EXPECT_FALSE( world->isEmptyAt( 0, 1, 2 ) );
}

TEST_F(OWTest,GetACube)
{
    WorldCube cubeA( 0, 2, 0 );
    world->put( cubeA );

    EXPECT_EQ( world->getAt( 0, 2, 0 ), cubeA );
}

TEST_F(OWTest,GetACubeDoesNotReturnSameCubes)
{
    WorldCube cubeA( 1, 1, 2);
    WorldCube cubeB( 2, 0, 2);

    cubeA->setBaseMaterial( Materials::Water );
    cubeB->setBaseMaterial( Materials::Dirt );

    world->put( cubeA );
    world->put( cubeB );

    EXPECT_EQ( world->getAt( 1, 1, 2 ), cubeA );
    EXPECT_EQ( world->getAt( 2, 0, 2 ), cubeB );
}

TEST_F(OWTest,GetAllCubesInWorld)
{
    WorldCube cubeA( 1, 1, 2);
    WorldCube cubeB( 2, 0, 2);
    WorldCube cubeC( 0, 0, 0);

    cubeA->setBaseMaterial( Materials::Water );
    cubeB->setBaseMaterial( Materials::Dirt );
    cubeC->setBaseMaterial( Materials::Rock );

    world->put( cubeA );
    world->put( cubeB );
    world->put( cubeC );

    // Test that all three cubes were in the world
    std::vector<WorldCube> cubes = world->getAllCubes();
    bool foundA = false, foundB = false, foundC = false;

    for ( int i = 0; i < cubes.size(); ++i )
    {
        if ( cubes[i] == cubeA ) { foundA = true; }
        if ( cubes[i] == cubeB ) { foundB = true; }
        if ( cubes[i] == cubeC ) { foundC = true; }
    }

    EXPECT_TRUE( foundA );
    EXPECT_TRUE( foundB );
    EXPECT_TRUE( foundC );
}

TEST_F(OWTest,CubeWorldVisitorVisitsAllCubes)
{

}
