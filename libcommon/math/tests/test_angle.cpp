/**
 * Unit tests for common/math/utils
 */
#include <googletest/googletest.h>
#include <math/angle.h>

using namespace Math;

TEST(Math, Angle_Degrees_Default_Constructor)
{
    Degrees<float> a;
    EXPECT_FLOAT_EQ( 0.0f, a.as<float>() );
}

TEST(Math, Angle_Degrees_Init)
{
    Degrees<float> a( 48.0f );
}
