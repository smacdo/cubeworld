#include <googletest/googletest.h>
#include <common/time.h>

TEST(TimeTests, DefaultConstructorIsZero)
{
    Time t;
    EXPECT_DOUBLE_EQ( 0.0, t.toDouble() );
}

TEST(TimeTests, IntConstructor)
{
    Time t( 42u );
    EXPECT_DOUBLE_EQ( 42.0, t.toDouble() );
}

TEST(TimeTests, FloatConstructor)
{
    Time t( 42.05f );
    EXPECT_DOUBLE_EQ( static_cast<double>(42.05f), t.toDouble() );
}

TEST(TimeTests, DoubleConstructor)
{
    Time t( 42.07 );
    EXPECT_DOUBLE_EQ( 42.07, t.toDouble() );
}

TEST(TimeTests, CopyConstructor)
{
    Time t( 455.04 );
    Time b( t );

    EXPECT_DOUBLE_EQ( 455.04, b.toDouble() );
}

TEST(TimeTests, Hours)
{
    Time t( 45612u );
    EXPECT_EQ( 12u, t.hours() );
}

TEST(TimeTests, Minutes)
{
    Time t( 45612u );
    EXPECT_EQ( 760u, t.minutes() );
}

TEST(TimeTests, Seconds)
{
    Time t( 45612u );
    EXPECT_EQ( 45612u, t.seconds() );
}

TEST(TimeTests, Milliseconds)
{
    Time t( 45612u );
    EXPECT_EQ( 45612000u, t.milliseconds() );
}

TEST(TimeTests, Microseconds)
{
    Time t( 45612u );
    EXPECT_EQ( 45612000000u, t.microseconds() );
}

TEST(TimeTests, Equality)
{
    Time a( 5u );
    Time b( 5u );
    Time c( 42u );

    EXPECT_TRUE( a == a );
    EXPECT_TRUE( a == b );
    EXPECT_TRUE( b == a );
    EXPECT_FALSE( a == c );
    EXPECT_FALSE( c == a );
}

TEST(TimeTests, Inequality)
{
    Time a( 5u );
    Time b( 5u );
    Time c( 42u );

    EXPECT_FALSE( a != a );
    EXPECT_FALSE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( c != a );
    EXPECT_TRUE( b != c );
}

TEST(TimeTests, LessThan)
{
    Time a( 2u );
    Time b( 3u );
    Time c( 4u );

    EXPECT_TRUE( a < b );
    EXPECT_TRUE( a < c );
    EXPECT_TRUE( b < c );

    EXPECT_FALSE( a < a );

    EXPECT_FALSE( c < a );
    EXPECT_FALSE( c < b );
    EXPECT_FALSE( b < a );
}

TEST(TimeTests, LessThanEquals)
{
    Time a( 2u );
    Time b( 3u );
    Time c( 4u );

    EXPECT_TRUE( a <= b );
    EXPECT_TRUE( a <= c );
    EXPECT_TRUE( b <= c );

    EXPECT_TRUE( a <= a );

    EXPECT_FALSE( c <= a );
    EXPECT_FALSE( c <= b );
    EXPECT_FALSE( b <= a );
}

TEST(TimeTests, GreaterThan)
{
    Time a( 2u );
    Time b( 3u );
    Time c( 4u );

    EXPECT_TRUE( c > b );
    EXPECT_TRUE( c > a );
    EXPECT_TRUE( b > a );

    EXPECT_FALSE( a > a );
    EXPECT_FALSE( a > b );
    EXPECT_FALSE( a > c );
    EXPECT_FALSE( b > c );
}

TEST(TimeTests, GreaterThanEqual)
{
    Time a( 2u );
    Time b( 3u );
    Time c( 4u );

    EXPECT_TRUE( c >= b );
    EXPECT_TRUE( c >= a );
    EXPECT_TRUE( b >= a );

    EXPECT_TRUE( a >= a );

    EXPECT_FALSE( a >= b );
    EXPECT_FALSE( a >= c );
    EXPECT_FALSE( b >= c );
}

TEST(TimeTests, Assignment)
{
    Time a( 562u );
    Time b( 326u );

    EXPECT_NE( a, b );

    a = b;

    EXPECT_EQ( a, b );
}
