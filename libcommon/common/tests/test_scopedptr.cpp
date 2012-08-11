#include <googletest/googletest.h>
#include <testing/testing.h>
#include <common/scopedptr.h>

class Resource
{
public:
    Resource( int& flag )
        : mFlag( flag ),
          mVal( 0 )
    {
        mFlag = 1;
    }

    ~Resource()
    {
        mFlag = 2;
    }

    void set( int v )
    {
        mVal = v;
    }

    int get() const
    {
        return mVal;
    }

private:
    Resource( const Resource& );
    Resource& operator = ( const Resource& );

private:
    int& mFlag;
    int mVal;
};

TEST(ScopedPointerTests,Creation)
{
    int flag = 0;
    
    {
        scoped_ptr<Resource> pR( new Resource( flag ) );
        EXPECT_EQ( 1, flag );
    }

    EXPECT_EQ( 2, flag );
}

TEST(ScopedPointerTests,CreationNullPointer)
{
    {
        scoped_ptr<const Resource> pR( NULL );
    }
}

TEST(ScopedPointerTests,CreationConstPointer)
{
    int flag = 0;
    
    {
        scoped_ptr<const Resource> pR( new Resource( flag ) );
        EXPECT_EQ( 1, flag );
    }

    EXPECT_EQ( 2, flag );
}

TEST(ScopedPointerTests,Reset)
{
    int a = 0;
    int b = 0;

    {
        scoped_ptr<const Resource> pA( new Resource( a ) );
        EXPECT_EQ( 1, a );
        EXPECT_EQ( 0, b );

        pA.reset( new Resource( b ) );

        EXPECT_EQ( 2, a );
        EXPECT_EQ( 1, b );
    }

    EXPECT_EQ( 2, a );
    EXPECT_EQ( 2, b );
}

TEST(ScopedPointerTests,ResetSamePointer)
{
    int a = 0;

    Resource * pResource = new Resource( a );

    {
        scoped_ptr<const Resource> pA( pResource );
        EXPECT_EQ( 1, a );

        pA.reset( pResource );

        EXPECT_EQ( 1, a );
    }

    EXPECT_EQ( 2, a );
}

TEST(ScopedPointerTests,ResetToNullPointer)
{
    int a = 0;
    Resource * pResource = new Resource( a );

    {
        scoped_ptr<const Resource> pA( pResource );
        EXPECT_EQ( 1, a );

        pA.reset( NULL );

        EXPECT_EQ( 2, a );
    }
}

TEST(ScopedPointerTests,DereferenceOperator)
{
    scoped_ptr<int> v( new int );
    *v = 42;

    EXPECT_EQ( 42, *v );
}

TEST(ScopedPointerDeathTests,DereferenceOperatorWithNull)
{
    scoped_ptr<int> v( NULL );

    UTest::assertDeath( true );
    EXPECT_DEATH( *v, "ASSERTION FAILED: mPtr != 0" );

    UTest::resetAssertDeath();
}

TEST(ScopedPointerTests,IndirectionOperator)
{
    int a;
    scoped_ptr<Resource> v( new Resource( a ) );

    EXPECT_EQ( 0, v->get() );

    v->set( 42 );
    EXPECT_EQ( 42, v->get() );
}

TEST(ScopedPointerDeathTests,IndirectionOperatorWithNull)
{
    scoped_ptr<Resource> v( NULL );

    UTest::assertDeath( true );
    EXPECT_DEATH( v->get(), "ASSERTION FAILED: mPtr != 0" );

    UTest::resetAssertDeath();
}

TEST(ScopedPointerTests,GetOperator)
{
    int *pA = new int;
    float *pB = new float;

    scoped_ptr<int> sA( pA );
    scoped_ptr<float> sB( pB );
    scoped_ptr<int> sC( NULL );

    EXPECT_EQ( pA, sA.get() );
    EXPECT_EQ( pB, sB.get() );
    EXPECT_EQ( NULL, sC.get() );
}

TEST(ScopedPointerTests,SwapOperator)
{
    int a = 0;
    int b = 0;

    Resource * pA = new Resource( a );
    Resource * pB = new Resource( b );

    {
        scoped_ptr<Resource> first( pA );
        scoped_ptr<Resource> second( pB );

        EXPECT_EQ( 1, a );
        EXPECT_EQ( 1, b );

        EXPECT_EQ( pA, first.get() );
        EXPECT_EQ( pB, second.get() );

        first.swap( second );

        EXPECT_EQ( 1, a );
        EXPECT_EQ( 1, b );

        EXPECT_EQ( pA, second.get() );
        EXPECT_EQ( pB, first.get() );
    }

    EXPECT_EQ( 2, a );
    EXPECT_EQ( 2, b );
}

TEST(ScopedPointerTests,NonMemberSwapFunction)
{
    int a = 0;
    int b = 0;

    Resource * pA = new Resource( a );
    Resource * pB = new Resource( b );

    {
        scoped_ptr<Resource> first( pA );
        scoped_ptr<Resource> second( pB );

        EXPECT_EQ( 1, a );
        EXPECT_EQ( 1, b );

        EXPECT_EQ( pA, first.get() );
        EXPECT_EQ( pB, second.get() );

        swap( first, second );

        EXPECT_EQ( 1, a );
        EXPECT_EQ( 1, b );

        EXPECT_EQ( pA, second.get() );
        EXPECT_EQ( pB, first.get() );
    }

    EXPECT_EQ( 2, a );
    EXPECT_EQ( 2, b );
}

TEST(ScopedPointerTests,BoolOperator)
{
    scoped_ptr<int> a( new int );
    scoped_ptr<int> b( NULL );

    EXPECT_TRUE( a );
    EXPECT_FALSE( b );
}
