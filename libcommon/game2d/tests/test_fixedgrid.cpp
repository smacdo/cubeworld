/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// Game includes
#include "game2d/fixedgrid.h"

// Unit test specific includes
#include <googletest/googletest.h>
#include <vector>

typedef FixedGrid<int> FGrid;
using ::testing::AssertionResult;
using ::testing::AssertionSuccess;
using ::testing::AssertionFailure;

const unsigned int SAMPLE_GRID_WIDTH  = 3;
const unsigned int SAMPLE_GRID_HEIGHT = 4;
const unsigned int SAMPLE_GRID_SIZE   = SAMPLE_GRID_WIDTH * SAMPLE_GRID_HEIGHT;
const int SAMPLE_GRID_VALUES[SAMPLE_GRID_SIZE] =
{
    4, 1, 9,
    9, 6, 7,
    3, 2, 0,
    1, 5, 8
};

const int* SAMPLE_GRID_VALUES_PTR = &SAMPLE_GRID_VALUES[0];

/////////////////////////////////////////////////////////////////////////
// Fixed grid test fixture
/////////////////////////////////////////////////////////////////////////
class FixedGridTest : public ::testing::Test
{
public:
    FixedGridTest();

protected:
    virtual void SetUp();

    unsigned int offset( unsigned int x, unsigned int y, unsigned int width );
    AssertionResult checkGrid( const FGrid& grid,
                               const int* expectedValues,
                               unsigned int expectedWidth,
                               unsigned int expectedHeight );

protected:
    const unsigned int sampleWidth;
    const unsigned int sampleHeight;
    const FGrid emptyGrid;
    FGrid sampleGrid;

};

typedef FixedGridTest FixedGridDeathTest;

/////////////////////////////////////////////////////////////////////////
// Fixed grid unit tests
/////////////////////////////////////////////////////////////////////////
TEST_F(FixedGridTest,FixedGrid_Constructor)
{
    const FGrid grid( 2, 3, 10 );

    const unsigned int W = 2;
    const unsigned int H = 3;
    const int VALUES[H*W] = { 10, 10,    // row 1
                              10, 10,    // row 2
                              10, 10 };  // row 3
    
    EXPECT_TRUE( checkGrid( grid, (const int*) VALUES, W, H ) );
}

TEST_F(FixedGridTest,FixedGrid_CopyConstructor)
{
    const FGrid grid( sampleGrid );

    // Values should match
    EXPECT_EQ( sampleGrid, grid );

    // Make sure the sample grid matches our provided static values above
    EXPECT_TRUE( checkGrid( grid,
                            SAMPLE_GRID_VALUES_PTR,
                            SAMPLE_GRID_WIDTH,
                            SAMPLE_GRID_HEIGHT ) );
}

TEST_F(FixedGridTest,MoveConstructor)
{
    // Not sure how to best test the move constructor... please
    // implement
}

TEST_F(FixedGridTest,AssignmentOperator)
{
    // First make sure it is set to 0...
    FGrid theWrongGrid( 5, 8, 42 );
    FGrid grid( theWrongGrid );

    // First assign it to the wrong thing
    grid = theWrongGrid;

    // Now assign it the correct grid
    grid = sampleGrid;

    EXPECT_NE( theWrongGrid, grid );
    EXPECT_NE( emptyGrid, grid );
    EXPECT_EQ( sampleGrid, grid );
}

TEST_F(FixedGridTest,AssignmentOperatorSelf)
{
    FGrid original( 3, 1, 0 );
    FGrid grid( 3, 1, 0 );

    // Make sure we can assign to ourself
    grid = grid;

    EXPECT_EQ( original, grid );
}

TEST_F(FixedGridTest,Insert_UpperLeft)
{
    FGrid grid( sampleGrid );
    FGrid chunk( 2, 3, 0 );

    // Set the chunk up and then insert it
    chunk.set( Point(0, 0), 3 ); chunk.set( Point(1, 0), 5 );
    chunk.set( Point(0, 1), 2 ); chunk.set( Point(1, 1), 6 );
    chunk.set( Point(0, 2), 4 ); chunk.set( Point(1, 2), 7 );

    // Insert the chunk into the grid
    grid.insert( Point( 0, 0 ), chunk );

    // Here's the expected new grid
    const unsigned int W = 3;
    const unsigned int H = 4;
    const int VALUES[H*W] = { 3, 5, 9,
                              2, 6, 7,
                              4, 7, 0,
                              1, 5, 8 };

    // Now verify everything matches up
    EXPECT_TRUE( checkGrid( grid, (const int*) VALUES, W, H ) );
}

TEST_F(FixedGridTest,Insert_Middle)
{
    FGrid grid( sampleGrid );
    FGrid chunk( 2, 3, 0 );

    // Set the chunk up and then insert it
    chunk.set( Point(0, 0), 3 ); chunk.set( Point(1, 0), 5 );
    chunk.set( Point(0, 1), 2 ); chunk.set( Point(1, 1), 6 );
    chunk.set( Point(0, 2), 4 ); chunk.set( Point(1, 2), 7 );

    // Insert the chunk into the grid
    grid.insert( Point( 1, 1 ), chunk );

    // Here's the expected new grid
    const unsigned int W = 3;
    const unsigned int H = 4;
    const int VALUES[H*W] = { 4, 1, 9,
                              9, 3, 5,
                              3, 2, 6,
                              1, 4, 7 };

    // Now verify everything matches up
    EXPECT_TRUE( checkGrid( grid, (const int*) VALUES, W, H ) );
}

TEST_F(FixedGridDeathTest,Insert_OutOfBounds)
{
    FGrid grid( sampleGrid );
    FGrid chunk( 2, 3, 0 );

    // Now verify everything matches up
    EXPECT_DEATH_IF_SUPPORTED( grid.insert( Point( 2, 1 ), chunk ),
                               "ASSERTION FAILED:" );
}

TEST_F(FixedGridTest,Clear)
{
    const FGrid clearGrid( sampleWidth, sampleHeight, 2 );
    FGrid grid( sampleGrid );

    grid.clear( 2 );

    EXPECT_NE( sampleGrid, grid );
    EXPECT_EQ( clearGrid, grid );
}

TEST_F(FixedGridTest,GetWithPoint)
{
    const FGrid grid( sampleGrid );

    EXPECT_EQ( grid.get(Point( 0, 0 )), 4 );
    EXPECT_EQ( grid.get(Point( 1, 1 )), 6 );
    EXPECT_EQ( grid.get(Point( 2, 1 )), 7 );
    EXPECT_EQ( grid.get(Point( 2, 3 )), 8 );
}

TEST_F(FixedGridTest,SetWithPoint)
{
    FGrid grid( sampleGrid );

    grid.set( Point(2, 1), 0 );
    EXPECT_EQ( 0, grid.get( Point(2, 1) ) );
    EXPECT_NE( sampleGrid, grid );

    grid.set( Point(2, 1), 7 );
    EXPECT_EQ( sampleGrid, grid );
}

TEST_F(FixedGridTest,WidthHeightAndSize)
{
    const FGrid grid( 9, 7, 0 );

    EXPECT_EQ( 9u, grid.width() );
    EXPECT_EQ( 7u, grid.height() );
    EXPECT_EQ( 63u, grid.size() );
}

///////////////////////////////////////////////////////////////////////////
// Internal helper methods
///////////////////////////////////////////////////////////////////////////
FixedGridTest::FixedGridTest()
    : sampleWidth( 3 ),
      sampleHeight( 4 ),
      emptyGrid( 3, 4, 0 ),
      sampleGrid( sampleWidth, sampleHeight, 0 )
{
    sampleGrid.set( Point(0, 0), 4 );
    sampleGrid.set( Point(1, 0), 1 );
    sampleGrid.set( Point(2, 0), 9 );

    sampleGrid.set( Point(0, 1), 9 );
    sampleGrid.set( Point(1, 1), 6 );
    sampleGrid.set( Point(2, 1), 7 );

    sampleGrid.set( Point(0, 2), 3 );
    sampleGrid.set( Point(1, 2), 2 );
    sampleGrid.set( Point(2, 2), 0 );
    
    sampleGrid.set( Point(0, 3), 1 );
    sampleGrid.set( Point(1, 3), 5 );
    sampleGrid.set( Point(2, 3), 8 );
}

void FixedGridTest::SetUp()
{
}

unsigned int FixedGridTest::offset( unsigned int x, unsigned int y, unsigned int width )
{
    return y * width + x;
}

AssertionResult FixedGridTest::checkGrid( const FGrid& actualGrid,
                                          const int* expectedValues,
                                          unsigned int expectedWidth,
                                          unsigned int expectedHeight )
{
    // Make sure expected values array isn't null
    if ( expectedValues == NULL )
    {
        return AssertionFailure()
            << "Array of expected values was null";
    }

    // Verify that the expected width and height are correct
    if ( actualGrid.width() != static_cast<int>(expectedWidth) )
    {
        return AssertionFailure()
            << "Expected width to be " << expectedWidth
            << ", but was " << actualGrid.width()
            << " instead";
    }

    if ( actualGrid.height() != static_cast<int>(expectedHeight) )
    {
        return AssertionFailure()
            << "Expected height to be " << expectedHeight
            << ", but was " << actualGrid.height()
            << " instead";
    }

    // Verify every element of the actual grid matches the provided
    // expected value array
    for ( unsigned int y = 0; y < expectedHeight; ++y )
    {
        for ( unsigned int x = 0; x < expectedWidth; ++x )
        {
            int gridVal  = actualGrid.get( Point(x, y) );
            int arrayVal = expectedValues[offset(x,y,expectedWidth)];

            if ( gridVal != arrayVal )
            {
                return AssertionFailure()
                    << "Expected value " << arrayVal << " at position ("
                    << x << ", " << y << "), but was "
                    << gridVal;
            }
        }
    }

    return AssertionSuccess();
}
