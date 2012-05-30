#include <googletest/googletest.h>
#include "engine/world.h"
#include "engine/cubedata.h"
#include "engine/constants.h"

class WorldTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        pWorld = new World( Constants::CHUNK_COLS * 4,
                            Constants::CHUNK_ROWS * 6,
                            Constants::CHUNK_DEPTH * 5 );
    }

    virtual void TearDown()
    {
        delete pWorld;
    }

    World * pWorld;
};

TEST_F(WorldTests,NewWorldShouldBeEmpty)
{
    for ( unsigned int z = 0; z < pWorld->depth(); ++z )
    {
        for ( unsigned int y = 0; y < pWorld->rows(); ++y )
        {
            for ( unsigned int x = 0; x < pWorld->cols(); ++x )
            {
                EXPECT_TRUE( pWorld->isEmptyAt( Point(x, y, z) ) );
            }
        }
    }
}

TEST_F(WorldTests,SettingACubeMakesItNotEmpty)
{
    EXPECT_TRUE( pWorld->isEmptyAt( Point(0, 0, 2) ) );

    pWorld->put( CubeData( EMATERIAL_GRASS ), Point( 0, 0, 2 ) );
    EXPECT_FALSE( pWorld->isEmptyAt( Point(0, 0, 2) ) );
}

TEST_F(WorldTests,GetACube)
{
    pWorld->put( CubeData( EMATERIAL_ROCK ), Point( 0, 2, 0 ) );

    EXPECT_EQ(pWorld->at( Point(0, 2, 0) ), CubeData( EMATERIAL_ROCK ) );
    EXPECT_NE(pWorld->at( Point(0, 2, 0) ), CubeData( EMATERIAL_GRASS ) );
}

TEST_F(WorldTests,GetACubeDoesNotReturnSameCubes)
{
    pWorld->put( CubeData( EMATERIAL_WATER ), Point( 1, 1, 2 ) );
    pWorld->put( CubeData( EMATERIAL_DIRT ), Point( 2, 0, 2 ) );

    EXPECT_EQ(pWorld->at( Point(1, 1, 2 ) ), CubeData( EMATERIAL_WATER ) );
    EXPECT_EQ(pWorld->at( Point(2, 0, 2 ) ), CubeData( EMATERIAL_DIRT ) );
}

TEST_F(WorldTests,PlacingCubesAcrossChunks)
{
    CubeData da( EMATERIAL_WATER );
    CubeData db( EMATERIAL_DIRT );
    CubeData dc( EMATERIAL_ROCK );

    Point pa( pWorld->cols() - 1, pWorld->rows() -1, 0 );
    Point pb( pWorld->cols() - 1, 0, pWorld->depth() - 1 );
    Point pc( 0, pWorld->rows() - 1, pWorld->depth() - 1);

    pWorld->put( da, pa );
    pWorld->put( db, pb );
    pWorld->put( dc, pc );

}

TEST_F(WorldTests,CubeWorldVisitorVisitsAllCubes)
{

}
