/**
 * Unit tests for templated vector4 class. These tests use float32 for the
 * numeric type, but can be adjusted to double precision.
 */
#include <googletest/googletest.h>
#include <math/vector.h>

TEST(Math, Vector4_DefaultContructor)
{
    const Vec4 v;
    EXPECT_TRUE( true );      // test here just to make sure it compiles
}

TEST(Math, Vector4_SizeTest)
{
    const Vec4 v( 1.0, 2.0, 3.0, 4.0 );
    EXPECT_EQ( sizeof(float) * 4, sizeof(v) );
}

TEST(Math, Vector4_MemoryArrayTest)
{
    // Makes sure that a vector is laid out linearly in memory
    Vec4 v[3];

    v[0] = Vec4( 1.0, 2.0, 3.0, 4.0 );
    v[1] = Vec4( 5.0, 6.0, 7.0, 8.0 );
    v[2] = Vec4( 9.0, 10.0, 11.0, 12.0 );

    const float * pVals = v[0].const_ptr();

    EXPECT_EQ( 1.0, *(pVals + 0) );
    EXPECT_EQ( 2.0, *(pVals + 1) );
    EXPECT_EQ( 3.0, *(pVals + 2) );
    EXPECT_EQ( 4.0, *(pVals + 3) );
    EXPECT_EQ( 5.0, *(pVals + 4) );
    EXPECT_EQ( 6.0, *(pVals + 5) );
    EXPECT_EQ( 7.0, *(pVals + 6) );
    EXPECT_EQ( 8.0, *(pVals + 7) );
    EXPECT_EQ( 9.0, *(pVals + 8) );
    EXPECT_EQ( 10.0, *(pVals + 9) );
    EXPECT_EQ( 11.0, *(pVals + 10) );
    EXPECT_EQ( 12.0, *(pVals + 11) );
}

TEST(Math, Vector4_PointerConstructor)
{
    float values[6] = { 3.0, 2.0, 5.0, -3.0, 6.0, 8.0 };
    Vec4 v( &values[1] );

    EXPECT_FLOAT_EQ(  2.0, v[0] );
    EXPECT_FLOAT_EQ(  5.0, v[1] );
    EXPECT_FLOAT_EQ( -3.0, v[2] );
    EXPECT_FLOAT_EQ(  6.0, v[3] );
}

TEST(Math, Vector4_ValueConstructor)
{
    const Vec4 v( 1.0, -2.0, 0.2, 3.5 );

    EXPECT_FLOAT_EQ(  1.0, v[0] );
    EXPECT_FLOAT_EQ( -2.0, v[1] );
    EXPECT_FLOAT_EQ(  0.2, v[2] );
    EXPECT_FLOAT_EQ(  3.5, v[3] );
}

TEST(Math, Vector4_CopyConstructor)
{
    const Vec4 a( 1.0, -2.0, 0.2, 3.5 );
    const Vec4 b( a );

    EXPECT_FLOAT_EQ(  1.0, b[0] );
    EXPECT_FLOAT_EQ( -2.0, b[1] );
    EXPECT_FLOAT_EQ(  0.2, b[2] );
    EXPECT_FLOAT_EQ(  3.5, b[3] );
}

TEST(Math, Vector4_ConstIndexOperatorRead)
{
    const Vec4 v( 1.0, -2.0, 0.2, 3.5 );

    EXPECT_FLOAT_EQ(  1.0, v[0] );
    EXPECT_FLOAT_EQ( -2.0, v[1] );
    EXPECT_FLOAT_EQ(  0.2, v[2] );
    EXPECT_FLOAT_EQ(  3.5, v[3] );
}

TEST(Math, Vector4_IndexOperatorWrite)
{
    Vec4 v( 1.0, -2.0, 0.2, 3.5 );

    v[0] = 2.0;
    v[1] = 0.2;
    v[2] = -1.0;
    v[3] = -2.5;

    EXPECT_EQ( Vec4( 2.0, 0.2, -1.0, -2.5 ), v );
}

TEST(Math, Vector4_ConstPointerAccess)
{
    Vec4 v( 1.0, 2.0, 3.0, 7.5 );
    const float * ptr = v.ptr();

    EXPECT_FLOAT_EQ( 1.0, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0, ptr[2] );
    EXPECT_FLOAT_EQ( 7.5, ptr[3] );
}

TEST(Math, Vector4_ConstConstPointerAccess)
{
    Vec4 v( 1.0, 2.0, 3.0, 7.5 );
    const float * ptr = v.const_ptr();

    EXPECT_FLOAT_EQ( 1.0, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0, ptr[2] );
    EXPECT_FLOAT_EQ( 7.5, ptr[3] );
}

TEST(Math, Vector4_NonConstPointerReadAndWrite)
{
    Vec4 v( 1.0, 2.0, 3.0, 7.5 );
    float * ptr = v.ptr();

    EXPECT_EQ( Vec4( 1.0, 2.0, 3.0, 7.5 ), v );

    ptr[0] = 5.0;
    ptr[1] = 6.0;
    ptr[2] = 7.0;
    ptr[3] = 9.2;

    EXPECT_EQ( Vec4( 5.0, 6.0, 7.0, 9.2 ), v );
}

TEST(Math, Vector4_Assignment)
{
    Vec4 a( 1.0, 2.0, 3.0, 0.1 );
    const Vec4 b( 3.0, 4.0, 5.0, 2.2 );
    
    a = b;

    EXPECT_NE( Vec4( 1.0, 2.0, 3.0, 0.1 ), a );
    EXPECT_EQ( Vec4( 3.0, 4.0, 5.0, 2.2 ), a );
}

TEST(Math, Vector4_EqualityOperator)
{
    const Vec4 a( 1.5, -0.2, 0.0, 1.0 );
    const Vec4 b( 1.5,  0.2, 0.0, 0.7 );
    const Vec4 c( 1.5, -0.2, 0.1, 1.0 );
    const Vec4 d( 1.5,  0.0,-0.2, 0.2 );
    const Vec4 e( 0.0,  1.5,-0.2, 0.2 );
    const Vec4 f( 1.5, -0.2, 0.0, 1.0 );

    EXPECT_EQ( a, f );
    EXPECT_EQ( a, a );
    EXPECT_FALSE( a == b );
    EXPECT_FALSE( a == c );
    EXPECT_FALSE( a == d );
    EXPECT_FALSE( a == e );
    EXPECT_TRUE( a == f );
    EXPECT_TRUE( a == a );
}

TEST(Math, Vector4_EqualityOperatorPrecision)
{
    const Vec4 a( 2.2, -0.333, 1.5, 0.0 );
    const Vec4 b( 4.4/2.0, -0.999/3.0, 0.5 * 3.0, 0.0 / 1.0 );

    EXPECT_EQ( a, b );
}

TEST(Math, Vector4_InequalityOperator)
{
    const Vec4 a( 1.5, -0.2, 0.0, 1.0 );
    const Vec4 b( 1.5,  0.2, 0.0, 0.7 );
    const Vec4 c( 1.5, -0.2, 0.1, 1.0 );
    const Vec4 d( 1.5,  0.0,-0.2, 0.2 );
    const Vec4 e( 0.0,  1.5,-0.2, 0.2 );
    const Vec4 f( 1.5, -0.2, 0.0, 1.0 );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != d );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}


TEST(Math, Vector4_Negation)
{
    Vec4 a( 2.0, 0.0, -1.0, 3.5 );
    a = -a;

    EXPECT_EQ( Vec4( -2.0, -0.0, 1.0, -3.5 ), a );
    EXPECT_EQ( Vec4( -2.0,  0.0, 1.0, -3.5 ), a );    // close
}

TEST(Math, Vector4_AdditionOperator)
{
    const Vec4 a( 3.0, 5.0, 9.0, 1.0 );
    const Vec4 b(-4.0, 6.0, 3.0, 2.0 );

    EXPECT_EQ( Vec4( -1.0, 11.0, 12.0, 3.0 ), a + b );
}

TEST(Math, Vector4_SelfAdditionOperator)
{
          Vec4 a( 3.0, 5.0, 9.0, 1.0 );
    const Vec4 b(-4.0, 6.0, 3.0, 2.0 );

    a += b;

    EXPECT_EQ( Vec4( -1.0, 11.0, 12.0, 3.0 ), a );
}

TEST(Math, Vector4_SubtractionOperator)
{
    const Vec4 a( 5.0, 2.0, -4.0,  0.0 );
    const Vec4 b(-1.0, 3.0,  8.0, -2.0 );
    const Vec4 c = a - b;
    
    EXPECT_EQ( Vec4( 6.0, -1.0, -12.0, 2.0 ), c );
}

TEST(Math, Vector4_SelfSubtractionOperator)
{
          Vec4 a( 5.0, 2.0, -4.0,  0.0 );
    const Vec4 b(-1.0, 3.0,  8.0, -2.0 );
    a -= b;
 
    EXPECT_EQ( Vec4( 6.0, -1.0, -12.0, 2.0 ), a );
}

TEST(Math, Vector4_MultiplyOperator)
{
    const Vec4 a( 3.0, 5.0, 9.0, 3.5 );
    const Vec4 b = a * 2.0;

    EXPECT_EQ( Vec4( 6.0, 10.0, 18.0, 7.0 ), b );
}

TEST(Math, Vector4_SelfMultiplyOperator)
{
    Vec4 a( 3.0, 5.0, 9.0, 3.5 );
    a *= 2.0;

    EXPECT_EQ( Vec4( 6.0, 10.0, 18.0, 7.0 ), a );
}

TEST(Math, Vector4_DivisionOperator)
{
    const Vec4 a( 3.0, 5.0, 9.0, 6.0 );
    const Vec4 b = a / 2.0;

    EXPECT_EQ( Vec4( 1.5, 2.5, 4.5, 3.0 ), b );
}

TEST(Math, Vector4_SelfDivisionOperator)
{
    Vec4 a( 3.0, 5.0, 9.0, 6.0 );
    a /= 2.0;

    EXPECT_EQ( Vec4( 1.5, 2.5, 4.5, 3. ), a );
}

TEST(Math, Vector4_XAccessor)
{
    Vec4 a( 1.0, 2.0, 3.0, 9.0 );
    Vec4 b( 6.0, 5.0, 4.0, 8.0 );

    EXPECT_EQ( 1.0, a.x() );
    EXPECT_EQ( 6.0, b.x() );
}

TEST(Math, Vector4_YAccessor)
{
    Vec4 a( 1.0, 2.0, 3.0, 9.0 );
    Vec4 b( 6.0, 5.0, 4.0, 8.0 );

    EXPECT_EQ( 2.0, a.y() );
    EXPECT_EQ( 5.0, b.y() );
}

TEST(Math, Vector4_ZAccessor)
{
    Vec4 a( 1.0, 2.0, 3.0, 9.0 );
    Vec4 b( 6.0, 5.0, 4.0, 8.0 );

    EXPECT_EQ( 3.0, a.z() );
    EXPECT_EQ( 4.0, b.z() );
}

TEST(Math, Vector4_WAccessor)
{
    Vec4 a( 1.0, 2.0, 3.0, 9.0 );
    Vec4 b( 6.0, 5.0, 4.0, 8.0 );

    EXPECT_EQ( 9.0, a.w() );
    EXPECT_EQ( 8.0, b.w() );
}

TEST(Math, Vector4_ZeroVector)
{
    const Vec4 a = Vec4::ZERO;

    EXPECT_FLOAT_EQ( 0.0, a[0] );
    EXPECT_FLOAT_EQ( 0.0, a[1] );
    EXPECT_FLOAT_EQ( 0.0, a[2] );
    EXPECT_FLOAT_EQ( 0.0, a[3] );
}

TEST(Math, Vector4_ZeroVectorIsZeroValueConstructed)
{
    const Vec4 a( 0.0, 0.0, 0.0, 0.0 );
    const Vec4 z = Vec4::ZERO;

    EXPECT_EQ( a, z );
}

TEST(Math, Vector4_Length)
{
    const Vec4 a( 1.0, 2.0, 3.0, 4.0 );
    EXPECT_FLOAT_EQ( 5.47722558f, length( a ) );
}

TEST(Math, Vector4_LengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, length( TVector4<float>::ZERO ) );
}

TEST(Math, Vector4_SquaredLength)
{
    const Vec4 a( 1.0, 2.0, 3.0, 4.0 );
    EXPECT_EQ( 30.0, lengthSquared( a ) );
}

TEST(Math, Vector4_SquareLengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, lengthSquared( TVector4<float>::ZERO ) );
}

TEST(Math, Vector4_Normalization)
{
    const Vec4 a( 3.0, 1.0, 2.0,-4.0 );
    const Vec4 n = normalized( a );

    EXPECT_EQ( Vec4( 0.547722557, 0.182574186, 0.365148371, -0.730296743), n );
}

TEST(Math, Vector4_Serialization)
{

}
