/**
 * Color class unit tests
 */
#include <game3d/color.h>
#include <googletest/googletest.h>

TEST(Color,DefaultColor)
{
    Color c;

    EXPECT_EQ( 1.0, c.r() );
    EXPECT_EQ( 1.0, c.g() );
    EXPECT_EQ( 1.0, c.b() );
    EXPECT_EQ( 1.0, c.a() );
}

TEST(Color,SimpleColor)
{
    Color c( 0.25, 0.50, 0.75 );

    EXPECT_EQ( 0.25, c.r() );
    EXPECT_EQ( 0.50, c.g() );
    EXPECT_EQ( 0.75, c.b() );
    EXPECT_EQ( 1.00, c.a() );
}

TEST(Color,ColorEqual)
{
    Color base( 0.2, 0.5, 0.9 );
    Color wrong( 0.2, 0.5, 0.8 );
    Color right( 0.2, 0.5, 0.9 );

    EXPECT_EQ( right, base );
    EXPECT_NE( wrong, base );
}

TEST(Color,ColorOutput)
{
    Color c( 0.25, 0.50, 0.75 );
}
