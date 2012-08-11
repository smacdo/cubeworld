/**
 * Color class unit tests
 */
#include <game3d/color.h>
#include <googletest/googletest.h>

TEST(Color,DefaultColor)
{
    Color c;

    EXPECT_FLOAT_EQ( 1.0f, c.r() );
    EXPECT_FLOAT_EQ( 1.0f, c.g() );
    EXPECT_FLOAT_EQ( 1.0f, c.b() );
    EXPECT_FLOAT_EQ( 1.0f, c.a() );
}

TEST(Color,SimpleColor)
{
    Color c( 0.25f, 0.50f, 0.75f );

    EXPECT_FLOAT_EQ( 0.25f, c.r() );
    EXPECT_FLOAT_EQ( 0.50f, c.g() );
    EXPECT_FLOAT_EQ( 0.75f, c.b() );
    EXPECT_FLOAT_EQ( 1.00f, c.a() );
}

TEST(Color,ColorEqual)
{
    Color base( 0.2f, 0.5f, 0.9f );
    Color wrong( 0.2f, 0.5f, 0.8f );
    Color right( 0.2f, 0.5f, 0.9f );

    EXPECT_EQ( right, base );
    EXPECT_NE( wrong, base );
}

TEST(Color,ColorOutput)
{
    Color c( 0.25f, 0.50f, 0.75f );
}
