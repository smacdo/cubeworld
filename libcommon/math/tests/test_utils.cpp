/**
 * Unit tests for common/math/utils
 */
#include <googletest/googletest.h>
#include <math/util.h>

using namespace Math;

//=========================================================================
// CloseEquals (fuzzy equality checking for floating point values)
//=========================================================================
TEST(Math,Utils_EqualsClose_Basic)
{
    // floating point
    EXPECT_TRUE( equalsClose( 42.0f, 42.0f ) );

    // double
    EXPECT_TRUE( equalsClose( 42.0f, 42.0f ) );

    // int
    EXPECT_TRUE( equalsClose( 42, 42 ) );
}

TEST(Math,Utils_EqualsClose_NotEquals)
{
    // floating point
    EXPECT_FALSE( equalsClose( 42.0f, -42.0f ) );

    // double
    EXPECT_FALSE( equalsClose( 42.0f, -42.0f ) );

    // int
    EXPECT_FALSE( equalsClose( 42, -42 ) );
}

TEST(Math,Utils_EqualsClose_Edges)
{
    EXPECT_TRUE( equalsClose( 1.0f, 0.99999999f ) );
    EXPECT_TRUE( equalsClose( 1.0f, 1.00000001f ) );
}

TEST(Math,Utils_EqualsClose_ZeroEdges)
{
    // float32
    EXPECT_TRUE( equalsClose( 0.0f, 0.000001f ) );
    EXPECT_TRUE( equalsClose( 0.0f,-0.000001f ) );
    EXPECT_TRUE( equalsClose( 0.0f,-0.0f      ) );

    // float64
    EXPECT_TRUE( equalsClose( 0.0f, 0.0000000001f ) );
    EXPECT_TRUE( equalsClose( 0.0f,-0.0000000001f ) );
    EXPECT_TRUE( equalsClose( 0.0f,-0.0000000000f  ) );
}

//===========================================================================
// Close equals zero
//===========================================================================
TEST(Math,Utils_IsZero_Zero_BasicTypes)
{
    EXPECT_TRUE( isZero(static_cast<int>(0)) );

    EXPECT_FALSE( isZero(static_cast<int>( 1  )) );
    EXPECT_FALSE( isZero(static_cast<int>( -1 )) );
    EXPECT_FALSE( isZero(static_cast<int>( 2  )) );

    EXPECT_TRUE( isZero(static_cast<unsigned int>( 0 )) );
    EXPECT_TRUE( isZero(static_cast<bool>( false )) );
    EXPECT_TRUE( isZero(static_cast<char>( 0 )) );
    EXPECT_TRUE( isZero(static_cast<long long>( 0 )) );
}

TEST(Math,Utils_IsZero_Zero)
{
    EXPECT_TRUE( isZero( 0.00f ) );
}

TEST(Math,Utils_IsZero_NotZero)
{
    EXPECT_FALSE( isZero( 0.1f ) );
}

TEST(Math,Utils_IsZero_WithinBounds)
{
    EXPECT_TRUE(  isZero( 0.000001f ) );
    EXPECT_TRUE(  isZero(-0.000001f ) );
}

TEST(Math,Utils_IsZero_OutsideBounds)
{
    EXPECT_FALSE( isZero( 0.00009f ) );
    EXPECT_FALSE( isZero(-0.00009f ) );
}

//===========================================================================
// Close compare to zero
//===========================================================================
TEST(Math,Utils_NotZero_True)
{
    EXPECT_TRUE(Math::notZero( 1 ));
    EXPECT_TRUE(Math::notZero( (double) 1.0f  ));
    EXPECT_TRUE(Math::notZero( (float)  1.0f ));
    EXPECT_TRUE(Math::notZero( (bool) true ));
}

TEST(Math,Utils_NotZero_False)
{
    EXPECT_FALSE(Math::notZero( 0 ));
    EXPECT_FALSE(Math::notZero( (double) 0.0f  ));
    EXPECT_FALSE(Math::notZero( (float)  0.0f ));
    EXPECT_FALSE(Math::notZero( (bool) false ));
}

//===========================================================================
// Clamp
//===========================================================================
TEST(Math,Utils_Clamp_LessThanMinimum)
{
    int a = 0, b = 2, v = -1;
    EXPECT_EQ( a, clamp( v, a, b ) );
}

TEST(Math,Utils_Clam_pMoreThanMinimum)
{
    int a = 0, b = 2, v = 3;
    EXPECT_EQ( b, clamp( v, a, b ) );
}

TEST(Math,Utils_Clamp_InBetween)
{
    int a = 0, b = 2, v = 1;
    EXPECT_EQ( v, clamp( v, a, b ) );
}

TEST(Math,Utils_Clamp_LessEquals)
{
    int a = 0, b = 2, v = 0;
    EXPECT_EQ( a, clamp( v, a, b ) );
}

//===========================================================================
// Wrap
//===========================================================================
TEST(Math,Utils_Wrap_ZeroToTen)
{
    EXPECT_EQ( 0, wrap( 0, 10 ) );
}

TEST(Math,Utils_Wrap_LessTenToTen)
{
    EXPECT_EQ( 5, wrap( 5, 10 ) );
}

TEST(Math,Utils_Wrap_MoreTenToTen)
{
    EXPECT_EQ( 2, wrap( 22, 10 ) );
}

//===========================================================================
// Snap
//===========================================================================
TEST(Math,Utils_Snap_SameValue)
{
    EXPECT_EQ( 2, snap( 2, 2 ) );
}

TEST(Math,Utils_Snap_GreaterMultiple)
{
    EXPECT_EQ( 4, snap( 4, 2 ) );
}

TEST(Math,Utils_Snap_HalfToGreaterMultiple)
{
    EXPECT_EQ( 6, snap( 5, 2 ) );
}

TEST(Math,Utils_Snap_LessHalfToLessMultiple)
{
    EXPECT_EQ( 5, snap( 6, 5 ) );
}

TEST(Math,Utils_Snaps_ToZeroAsMultiple)
{
    EXPECT_EQ( 3, snap( 1, 3 ) );
}

TEST(Math,Utils_Snaps_NearestNegativeMultipleIfNegative)
{
    EXPECT_EQ( -10, snap( -9, 5 ) );
}

//===========================================================================
// square and cube
//===========================================================================
TEST(Math,Utils_Square_Value)
{
    EXPECT_EQ( 25, square( 5 ) );
    EXPECT_EQ( 0, square( 0 ) );
    EXPECT_EQ( 1, square( 1 ) );
}

TEST(Math,Utils_Cube_Value)
{
    EXPECT_EQ( 125, cube( 5 ) );
    EXPECT_EQ( 0, cube( 0 ) );
    EXPECT_EQ( 1, cube( 1 ) );
}

TEST(Math,Utils_ClampAngle_IntValues)
{
    EXPECT_EQ( 270, clampAngle( -90 ) );
    EXPECT_EQ( 0,   clampAngle( 0 ) );
    EXPECT_EQ( 180, clampAngle( 180 ) );
    EXPECT_EQ( 0,   clampAngle( 360 ) );
    EXPECT_EQ( 60,  clampAngle( 420 ) );
    EXPECT_EQ( 0,   clampAngle( 720 ) );
}

TEST(Math,Utils_ClampAngle_FloatValues)
{
    EXPECT_FLOAT_EQ( 270.0f, clampAngle( -90.0f ) );
    EXPECT_FLOAT_EQ( 0.0f,   clampAngle( 0.0f ) );
    EXPECT_FLOAT_EQ( 180.0f, clampAngle( 180.0f ) );
    EXPECT_FLOAT_EQ( 0.0f,   clampAngle( 360.0f ) );
    EXPECT_FLOAT_EQ( 60.0f,  clampAngle( 420.0f ) );
    EXPECT_FLOAT_EQ( 0.0f,   clampAngle( 720.0f ) );
}

TEST(Math,Utils_ClampAngle_DoubleValues)
{
    EXPECT_FLOAT_EQ( 270.0f, clampAngle( -90.0f ) );
    EXPECT_FLOAT_EQ( 0.0f,   clampAngle( 0.0f ) );
    EXPECT_FLOAT_EQ( 180.0f, clampAngle( 180.0f ) );
    EXPECT_FLOAT_EQ( 0.0f,   clampAngle( 360.0f ) );
    EXPECT_FLOAT_EQ( 60.0f,  clampAngle( 420.0f ) );
    EXPECT_FLOAT_EQ( 0.0f,   clampAngle( 720.0f ) );
}

TEST(Math,Utils_NextPowerOfTwo_Values)
{
    EXPECT_EQ( 0, nextPowerOfTwo( 0 ) );
    EXPECT_EQ( 1, nextPowerOfTwo( 1 ) );
    EXPECT_EQ( 2, nextPowerOfTwo( 2 ) );
    EXPECT_EQ( 4, nextPowerOfTwo( 3 ) );
    EXPECT_EQ( 8, nextPowerOfTwo( 5 ) );
    EXPECT_EQ( 8, nextPowerOfTwo( 6 ) );
    EXPECT_EQ( 8, nextPowerOfTwo( 7 ) );
    EXPECT_EQ( 8, nextPowerOfTwo( 8 ) );
}
