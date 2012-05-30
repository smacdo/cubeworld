#include <googletest/googletest.h>
#include "engine/worldchunk.h"
#include "engine/material.h"
#include "engine/constants.h"
#include "engine/point.h"

class WorldChunkTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        pChunk = new WorldChunk;
    }

    virtual void TearDown()
    {
        delete pChunk;
    }

    ::testing::AssertionResult IsEmpty( const WorldChunk *pChunkIn,
                                        const Point& p )
    {
        if ( pChunkIn->isEmptyAt( p ) )
        {
            return ::testing::AssertionSuccess();
        }
        else
        {
            return ::testing::AssertionFailure()
                << "Chunk cube was not empty at chunk position "
                << p;
        }   
    }

    ::testing::AssertionResult IsOfType( const WorldChunk *pChunkIn,
                                         EMaterialType mat,
                                         const Point& p )
    {
        CubeData cube      = pChunkIn->at( p );
        EMaterialType cmat = cube.materialType();

        if ( cmat == mat )
        {
            return ::testing::AssertionSuccess();
        }
        else
        {
            return ::testing::AssertionFailure()
                << "Expected material type " << Util::ToString( mat )
                << " at point "              << p
                << ", got "                  << Util::ToString( cmat )
                << " instead";
        }
    }

    WorldChunk *pChunk;
};

TEST_F(WorldChunkTests,DimensionsMatchConstantValues)
{
    EXPECT_EQ( Constants::CHUNK_COLS,  pChunk->TOTAL_COLS );
    EXPECT_EQ( Constants::CHUNK_ROWS,  pChunk->TOTAL_ROWS );
    EXPECT_EQ( Constants::CHUNK_DEPTH, pChunk->TOTAL_DEPTH );
}

TEST_F(WorldChunkTests,NewChunkShouldBeEmpty)
{
    EXPECT_EQ( 0u, pChunk->cubeCount() );

    for ( unsigned int x = 0; x < pChunk->TOTAL_COLS; ++x )
    {
        for ( unsigned int y = 0; y < pChunk->TOTAL_ROWS; ++y )
        {
            for ( unsigned int z = 0; z < pChunk->TOTAL_DEPTH; ++z )
            {
                EXPECT_TRUE( IsEmpty( pChunk, Point( x, y, z ) ) );
            }
        }
    }
}

TEST_F(WorldChunkTests,PlacedCubeIsSaved)
{
    // Set three cubes
    pChunk->put( CubeData( EMATERIAL_GRASS ), Point( 2, 5, 6 ) );
    pChunk->put( CubeData( EMATERIAL_WOOD ), Point( 24, 5, 0 ) );
    pChunk->put( CubeData( EMATERIAL_ROCK ), Point( 31, 0, 12 ) );

    // Check type, make sure set (in random order)
    EXPECT_FALSE( IsOfType( pChunk, EMATERIAL_DIRT, Point( 24, 5, 0 ) ) );

    EXPECT_TRUE(  IsOfType( pChunk, EMATERIAL_WOOD, Point( 24, 5, 0 ) ) );
    EXPECT_TRUE(  IsOfType( pChunk, EMATERIAL_ROCK, Point( 31, 0, 12 ) ) );
    EXPECT_TRUE(  IsOfType( pChunk, EMATERIAL_GRASS, Point( 2, 5, 6 ) ) );
}
