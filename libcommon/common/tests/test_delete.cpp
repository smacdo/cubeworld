/**
 * Unit tests for the memory deleter. Do NOT THREAD
 */
#include <googletest/googletest.h>
#include <common/delete.h>
#include <ostream>
#include <vector>
#include <deque>
#include <list>

#include "common/delete.h"

unsigned int GNumObjectsCreated = 0;
unsigned int GNumObjectsDeleted = 0;
unsigned int GNumObjectsAlive   = 0;

class DeleteTest : public testing::Test
{
protected:
    virtual void SetUp()
    {
        GNumObjectsCreated = 0;
        GNumObjectsDeleted = 0;
        GNumObjectsAlive   = 0;
    }

    virtual void TearDown()
    {
        ASSERT_EQ( GNumObjectsCreated, GNumObjectsDeleted );
        EXPECT_EQ( 0u, GNumObjectsAlive );
    }
};

class TestDummy
{
public:
    TestDummy()
        : mpAlive(NULL)
    {
        GNumObjectsCreated++;
        GNumObjectsAlive++;
    }

    TestDummy( bool * pAlive )
        : mpAlive( pAlive )
    {
        GNumObjectsCreated++;
        GNumObjectsAlive++;

        *mpAlive = true;
    }

    ~TestDummy()
    {
        GNumObjectsDeleted++;
        GNumObjectsAlive--;

        if ( mpAlive )
        {
            *mpAlive = false;
        }
    }

    void attach( bool * pAlive )
    {
        mpAlive = pAlive;

        if ( mpAlive )
        {
            *mpAlive = true;
        }
    }

private:
    bool * mpAlive;
};

TEST_F(DeleteTest,VerifyTestDummy)
{
    bool aliveA  = false;
    bool aliveB  = false;

    TestDummy *pA = new TestDummy( &aliveA );
    EXPECT_TRUE( aliveA );
    EXPECT_FALSE( aliveB );

    TestDummy *pB = new TestDummy( &aliveB );
    EXPECT_TRUE( aliveA );
    EXPECT_TRUE( aliveB );

    delete pA;
    EXPECT_FALSE( aliveA );
    EXPECT_TRUE( aliveB );

    delete pB;
    EXPECT_FALSE( aliveA );
    EXPECT_FALSE( aliveA );
}

TEST_F(DeleteTest,DeletePointer)
{
    bool alive   = false;

    TestDummy *pA = new TestDummy( &alive );
    EXPECT_TRUE( alive );
    Delete( pA );

    // Make sure destructor was called
    EXPECT_FALSE( alive );
    EXPECT_TRUE( pA == NULL );
}

TEST_F(DeleteTest,DeletePointerArray)
{
    bool aliveA = false, aliveB = false, aliveC = false;
    TestDummy * pA = new TestDummy[ 3 ];

    pA[0].attach( &aliveA );
    pA[1].attach( &aliveB );
    pA[2].attach( &aliveC );

    EXPECT_TRUE( aliveA );
    EXPECT_TRUE( aliveB );
    EXPECT_TRUE( aliveC );

    DeleteArray( pA );

    EXPECT_FALSE( aliveA );
    EXPECT_FALSE( aliveB );
    EXPECT_FALSE( aliveC );
}

TEST_F(DeleteTest,DeleteVectorOfPointers)
{
    bool aliveA = false;
    bool aliveB = false;
    bool aliveC = false;

    std::vector<TestDummy*> v;
    v.push_back( new TestDummy( &aliveA ) );
    v.push_back( new TestDummy( &aliveB ) );
    v.push_back( new TestDummy( &aliveC ) );

    EXPECT_TRUE( aliveA );
    EXPECT_TRUE( aliveB );
    EXPECT_TRUE( aliveC );

    EXPECT_EQ( 3u, DeletePointerContainer( v ) );
    EXPECT_FALSE( aliveA );
    EXPECT_FALSE( aliveB );
    EXPECT_FALSE( aliveC );
}

TEST_F(DeleteTest,DeleteMapOfPointers)
{
    bool aliveA = false;
    bool aliveB = false;
    bool aliveC = false;

    std::map<int, TestDummy*> v;
    v.insert( std::pair<int, TestDummy*>( 0, new TestDummy( &aliveA ) ) );
    v.insert( std::pair<int, TestDummy*>( 1, new TestDummy( &aliveB ) ) );
    v.insert( std::pair<int, TestDummy*>( 2, new TestDummy( &aliveC ) ) );

    EXPECT_TRUE( aliveA );
    EXPECT_TRUE( aliveB );
    EXPECT_TRUE( aliveC );

    EXPECT_EQ( 3u, DeleteMapPointers( v ) );
    EXPECT_FALSE( aliveA );
    EXPECT_FALSE( aliveB );
    EXPECT_FALSE( aliveC );
}

TEST_F(DeleteTest,DeleteDequeOfPointers)
{
    bool aliveA = false;
    bool aliveB = false;
    bool aliveC = false;

    std::deque<TestDummy*> v;
    v.push_back( new TestDummy( &aliveA ) );
    v.push_back( new TestDummy( &aliveB ) );
    v.push_back( new TestDummy( &aliveC ) );

    EXPECT_TRUE( aliveA );
    EXPECT_TRUE( aliveB );
    EXPECT_TRUE( aliveC );

    EXPECT_EQ( 3u, DeletePointerContainer( v ) );
    EXPECT_FALSE( aliveA );
    EXPECT_FALSE( aliveB );
    EXPECT_FALSE( aliveC );
}

TEST_F(DeleteTest,DeleteStackOfPointers)
{
    bool aliveA = false;
    bool aliveB = false;
    bool aliveC = false;

    std::list<TestDummy*> v;
    v.push_front( new TestDummy( &aliveA ) );
    v.push_front( new TestDummy( &aliveB ) );
    v.push_back( new TestDummy( &aliveC ) );

    EXPECT_TRUE( aliveA );
    EXPECT_TRUE( aliveB );
    EXPECT_TRUE( aliveC );

    EXPECT_EQ( 3u, DeletePointerContainer( v ) );
    EXPECT_FALSE( aliveA );
    EXPECT_FALSE( aliveB );
    EXPECT_FALSE( aliveC );
}

