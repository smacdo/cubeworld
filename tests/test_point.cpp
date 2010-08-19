#include "gtest.h"
#include "point.h"

TEST(Point,DefaultPointConstructorZero)
{
    const Point p;

    EXPECT_TRUE( p[0] == 0 );
    EXPECT_TRUE( p[1] == 0 );
    EXPECT_TRUE( p[2] == 0 );
}

TEST(Point,SimplePointConstructor)
{
    const Point p( 0, 1, 2 );

    EXPECT_TRUE( p[0] == 0 );
    EXPECT_TRUE( p[1] == 1 );
    EXPECT_TRUE( p[2] == 2 );
}

TEST(Point,PointCopyConstructor)
{
    const Point p( 0, 1, 2 );
    const Point c( p );

    EXPECT_TRUE( c[0] == 0 );
    EXPECT_TRUE( c[1] == 1 );
    EXPECT_TRUE( c[2] == 2 );
}

TEST(Point,PointAssignmentOperator)
{
    const Point a( 0, 1, 2 );
    Point b( 0, 0, 0 );

    // stop compiler optmizing the assignment out (copy construct)
    b[0] = 2;

    b = a;

    EXPECT_EQ( a, b );
}

TEST(Point,PointEquality)
{
    const Point a( 1, 2, 3 );
    const Point b( 1, 2, 3 );

    EXPECT_TRUE( a == b );
    ASSERT_EQ( a, b );
}

TEST(Point,PointEqualityNegated)
{
    const Point a( 1, 2, 3 );
    const Point b( 3, 2, 1 );

    EXPECT_FALSE( a == b );
}

TEST(Point,PointInequality)
{
    const Point a( 1, 2, 3 );
    const Point b( 5, 6, 7 );

    EXPECT_TRUE( a != b );
    ASSERT_NE( a, b );
}

TEST(Point,PointInequalityNegated)
{
    const Point a( 1, 2, 3 );
    const Point b( 1, 2, 3 );

    EXPECT_FALSE( a != b );
}

TEST(Point,PointAccessor)
{
    const Point a( 1, 5, 9 );

    EXPECT_EQ( 1, a[0] );
    EXPECT_EQ( 5, a[1] );
    EXPECT_EQ( 9, a[2] );
}

TEST(Point,PointSetter)
{
    Point a( 1, 5, 9 );
    
    a[0] = 2;
    a[1] = 4;
    a[2] = 7;

    EXPECT_EQ( 2, a[0] );
    EXPECT_EQ( 4, a[1] );
    EXPECT_EQ( 7, a[2] );
}

TEST(Point,PointIsZeroIsTrueOnZero)
{
    const Point a( 0, 0, 0 );
    EXPECT_TRUE( a.isZero() );
}

TEST(Point,PointIsZeroIsFalseOnNotZero)
{
    const Point a( 0, 0, 1 );
    EXPECT_FALSE( a.isZero() );
}
