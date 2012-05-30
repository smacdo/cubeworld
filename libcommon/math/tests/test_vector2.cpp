/**
 * Unit tests for templated vector2 class. These tests use float32 for the
 * numeric type, but can be adjusted to double precision.
 */
#include <googletest/googletest.h>
#include <math/vector.h>

TEST(Math, Vector2_DefaultContructor)
{
    const Vec2 v;
    EXPECT_TRUE( true );      // test here just to make sure it compiles
}

TEST(Math, Vector2_SizeTest)
{
    const Vec2 v( 1.0, 2.0 );
    EXPECT_EQ( sizeof(float) * 2, sizeof(v) );
}

TEST(Math, Vector2_MemoryArrayTest)
{
    // Makes sure that a vector is laid out linearly in memory
    Vec2 v[3];

    v[0] = Vec2( 1.0, 2.0 );
    v[1] = Vec2( 3.0, 4.0 );
    v[2] = Vec2( 5.0, 6.0 );

    const float * pVals = v[0].const_ptr();

    EXPECT_EQ( 1.0, *(pVals + 0) );
    EXPECT_EQ( 2.0, *(pVals + 1) );
    EXPECT_EQ( 3.0, *(pVals + 2) );
    EXPECT_EQ( 4.0, *(pVals + 3) );
    EXPECT_EQ( 5.0, *(pVals + 4) );
    EXPECT_EQ( 6.0, *(pVals + 5) );
}

TEST(Math, Vector2_PointerConstructor)
{
    float values[5] = { 3.0, 2.0, 5.0, -3.0, 6.0 };
    Vec2 v( &values[1] );

    EXPECT_FLOAT_EQ(  2.0, v[0] );
    EXPECT_FLOAT_EQ(  5.0, v[1] );
}

TEST(Math, Vector2_ValueConstructor)
{
    const Vec2 v( 1.0, -2.0 );

    EXPECT_FLOAT_EQ(  1.0, v[0] );
    EXPECT_FLOAT_EQ( -2.0, v[1] );
}

TEST(Math, Vector2_CopyConstructor)
{
    const Vec2 a( 1.0, -2.0 );
    const Vec2 b( a );

    EXPECT_FLOAT_EQ(  1.0, b[0] );
    EXPECT_FLOAT_EQ( -2.0, b[1] );
}

TEST(Math, Vector2_ConstIndexOperatorRead)
{
    const Vec2 v( 1.0, -2.0 );

    EXPECT_FLOAT_EQ(  1.0, v[0] );
    EXPECT_FLOAT_EQ( -2.0, v[1] );
}

TEST(Math, Vector2_IndexOperatorWrite)
{
    Vec2 v( 1.0, -2.0 );

    v[0] = 2.0;
    v[1] = 0.2;

    EXPECT_EQ( Vec2( 2.0, 0.2 ), v );
}

TEST(Math, Vector2_ConstPointerAccess)
{
    Vec2 v( 1.0, 2.0 );
    const float * ptr = v.ptr();

    EXPECT_FLOAT_EQ( 1.0, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0, ptr[1] );
}

TEST(Math, Vector2_ConstConstPointerAccess)
{
    Vec2 v( 1.0, 2.0 );
    const float * ptr = v.const_ptr();

    EXPECT_FLOAT_EQ( 1.0, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0, ptr[1] );
}

TEST(Math, Vector2_NonConstPointerReadAndWrite)
{
    Vec2 v( 1.0, 2.0 );
    float * ptr = v.ptr();

    EXPECT_EQ( Vec2( 1.0, 2.0 ), v );

    ptr[0] = 5.0;
    ptr[1] = 6.0;

    EXPECT_EQ( Vec2( 5.0, 6.0 ), v );
}

TEST(Math, Vector2_Assignment)
{
    Vec2 a( 1.0, 2.0 );
    const Vec2 b( 3.0, 4.0 );
    
    a = b;

    EXPECT_NE( Vec2( 1.0, 2.0 ), a );
    EXPECT_EQ( Vec2( 3.0, 4.0 ), a );
}

TEST(Math, Vector2_EqualityOperator)
{
    const Vec2 a( 1.5, -0.2 );
    const Vec2 b( 1.5,  0.2 );
    const Vec2 c( 0.5, -0.2 );
    const Vec2 e( 0.0,  0.5 );
    const Vec2 f( 1.5, -0.2 );

    EXPECT_EQ( a, f );
    EXPECT_EQ( a, a );
    EXPECT_FALSE( a == b );
    EXPECT_FALSE( a == c );
    EXPECT_FALSE( a == e );
    EXPECT_TRUE( a == f );
    EXPECT_TRUE( a == a );
}

TEST(Math, Vector2_EqualityOperatorPrecision)
{
    const Vec2 a( 2.2, -0.333 );
    const Vec2 b( 4.4/2.0, -0.999/3.0 );

    EXPECT_EQ( a, b );
}

TEST(Math, Vector2_InequalityOperator)
{
    const Vec2 a( 1.5, -0.2 );
    const Vec2 b( 1.5,  0.2 );
    const Vec2 c( 0.5, -0.2 );
    const Vec2 e( 0.0,  0.5 );
    const Vec2 f( 1.5, -0.2 );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}


TEST(Math, Vector2_Negation)
{
    Vec2 a( 2.0, 0.0 );
    a = -a;

    EXPECT_EQ( Vec2( -2.0, -0.0 ), a );
    EXPECT_EQ( Vec2( -2.0,  0.0 ), a );    // close
}

TEST(Math, Vector2_AdditionOperator)
{
    const Vec2 a( 3.0, 5.0 );
    const Vec2 b(-4.0, 6.0 );

    EXPECT_EQ( Vec2( -1.0, 11.0 ), a + b );
}

TEST(Math, Vector2_SelfAdditionOperator)
{
          Vec2 a( 3.0, 5.0 );
    const Vec2 b(-4.0, 6.0 );

    a += b;

    EXPECT_EQ( Vec2( -1.0, 11.0 ), a );
}

TEST(Math, Vector2_SubtractionOperator)
{
    const Vec2 a( 5.0, 2.0 );
    const Vec2 b(-1.0, 3.0 );
    const Vec2 c = a - b;
    
    EXPECT_EQ(   6.0, c[0] );
    EXPECT_EQ(  -1.0, c[1] );
}

TEST(Math, Vector2_SelfSubtractionOperator)
{
    Vec2       a( 5.0, 2.0 );
    const Vec2 b(-1.0, 3.0 );
    a -= b;
    
    EXPECT_EQ(   6.0, a[0] );
    EXPECT_EQ(  -1.0, a[1] );
}

TEST(Math, Vector2_MultiplyOperator)
{
    const Vec2 a( 3.0, 5.0 );
    const Vec2 b = a * 2.0;

    EXPECT_EQ( Vec2( 6.0, 10.0 ), b );
}

TEST(Math, Vector2_SelfMultiplyOperator)
{
    Vec2 a( 3.0, 5.0 );
    a *= 2.0;

    EXPECT_EQ( Vec2( 6.0, 10.0 ), a );
}

TEST(Math, Vector2_DivisionOperator)
{
    const Vec2 a( 3.0, 5.0 );
    const Vec2 b = a / 2.0;

    EXPECT_EQ( Vec2( 1.5, 2.5 ), b );
}

TEST(Math, Vector2_SelfDivisionOperator)
{
    Vec2 a( 3.0, 5.0 );
    a /= 2.0;

    EXPECT_EQ( Vec2( 1.5, 2.5 ), a );
}

TEST(Math, Vector2_XAccessor)
{
    Vec2 a( 1.0, 2.0 );
    Vec2 b( 6.0, 5.0 );

    EXPECT_EQ( 1.0, a.x() );
    EXPECT_EQ( 6.0, b.x() );
}

TEST(Math, Vector2_YAccessor)
{
    Vec2 a( 1.0, 2.0 );
    Vec2 b( 6.0, 5.0 );

    EXPECT_EQ( 2.0, a.y() );
    EXPECT_EQ( 5.0, b.y() );
}

TEST(Math, Vector2_ZeroVector)
{
    const Vec2 a = Vec2::ZERO;

    EXPECT_EQ( a[0], 0.0 );
    EXPECT_EQ( a[1], 0.0 );
}

TEST(Math, Vector2_ZeroVectorIsZeroValueConstructed)
{
    const Vec2 a( 0.0, 0.0 );
    const Vec2 z = Vec2::ZERO;

    EXPECT_EQ( a, z );
}

TEST(Math, Vector2_Length)
{
    const Vec2 a( 1.0, 2.0 );
    EXPECT_FLOAT_EQ( 2.23606798, length( a ) );
}

TEST(Math, Vector2_LengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, length( TVector2<float>::ZERO ) );
}

TEST(Math, Vector2_SquaredLength)
{
    const Vec2 a( 1.0, 2.0 );
    EXPECT_EQ( 5.0, lengthSquared( a ) );
}

TEST(Math, Vector2_SquareLengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, lengthSquared( TVector2<float>::ZERO ) );
}

TEST(Math, Vector2_Normalization)
{
    const Vec2 a( 3.0, 1.0 );
    const Vec2 n = normalized( a );

    EXPECT_EQ( Vec2( 0.948683298, 0.316227766 ), n );
}
