/**
 * Unit tests for common/math/utils
 */
#include <googletest/googletest.h>
#include <math/conversion.h>

using namespace Math;

TEST(Math,Conversion_Rad2Deg_Values)
{
    // pi constant deliberately not used
    EXPECT_FLOAT_EQ( 0.0f,   rad2deg( 0.00000000f ) );
    EXPECT_FLOAT_EQ( 90.0f,  rad2deg( 1.57079633f ) );
    EXPECT_FLOAT_EQ( 180.0f, rad2deg( 3.14159265f ) );
    EXPECT_FLOAT_EQ( 360.0f, rad2deg( 6.28318531f ) );
    EXPECT_FLOAT_EQ( 420.0f, rad2deg( 7.33038286f ) );
}

TEST(Math,Conversion_Deg2Rad_Values)
{
    // pi constant deliberately not used
    EXPECT_FLOAT_EQ( 0.00000000f, deg2rad( 0.0f ) );
    EXPECT_FLOAT_EQ( 1.57079633f, deg2rad( 90.0f ) );
    EXPECT_FLOAT_EQ( 3.14159265f, deg2rad( 180.0f ) );
    EXPECT_FLOAT_EQ( 6.28318531f, deg2rad( 360.0f ) );
    EXPECT_FLOAT_EQ( 7.33038286f, deg2rad( 420.0f ) );
}
