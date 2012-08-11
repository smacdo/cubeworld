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
    const Vec4 v( 1.0f, 2.0f, 3.0f, 4.0f );
    EXPECT_EQ( sizeof(float) * 4, sizeof(v) );
}

TEST(Math, Vector4_MemoryArrayTest)
{
    // Makes sure that a vector is laid out linearly in memory
    Vec4 v[3];

    v[0] = Vec4( 1.0f, 2.0f, 3.0f, 4.0f );
    v[1] = Vec4( 5.0f, 6.0f, 7.0f, 8.0f );
    v[2] = Vec4( 9.0f, 10.0f, 11.0f, 12.0f );

    const float * pVals = v[0].const_ptr();

    EXPECT_FLOAT_EQ( 1.0f, *(pVals + 0) );
    EXPECT_FLOAT_EQ( 2.0f, *(pVals + 1) );
    EXPECT_FLOAT_EQ( 3.0f, *(pVals + 2) );
    EXPECT_FLOAT_EQ( 4.0f, *(pVals + 3) );
    EXPECT_FLOAT_EQ( 5.0f, *(pVals + 4) );
    EXPECT_FLOAT_EQ( 6.0f, *(pVals + 5) );
    EXPECT_FLOAT_EQ( 7.0f, *(pVals + 6) );
    EXPECT_FLOAT_EQ( 8.0f, *(pVals + 7) );
    EXPECT_FLOAT_EQ( 9.0f, *(pVals + 8) );
    EXPECT_FLOAT_EQ( 10.0f, *(pVals + 9) );
    EXPECT_FLOAT_EQ( 11.0f, *(pVals + 10) );
    EXPECT_FLOAT_EQ( 12.0f, *(pVals + 11) );
}

TEST(Math, Vector4_PointerConstructor)
{
    float values[6] = { 3.0f, 2.0f, 5.0f, -3.0f, 6.0f, 8.0f };
    Vec4 v( &values[1] );

    EXPECT_FLOAT_EQ(  2.0f, v[0] );
    EXPECT_FLOAT_EQ(  5.0f, v[1] );
    EXPECT_FLOAT_EQ( -3.0f, v[2] );
    EXPECT_FLOAT_EQ(  6.0f, v[3] );
}

TEST(Math, Vector4_ValueConstructor)
{
    const Vec4 v( 1.0f, -2.0f, 0.2f, 3.5f );

    EXPECT_FLOAT_EQ(  1.0f, v[0] );
    EXPECT_FLOAT_EQ( -2.0f, v[1] );
    EXPECT_FLOAT_EQ(  0.2f, v[2] );
    EXPECT_FLOAT_EQ(  3.5f, v[3] );
}

TEST(Math, Vector4_CopyConstructor)
{
    const Vec4 a( 1.0f, -2.0f, 0.2f, 3.5f );
    const Vec4 b( a );

    EXPECT_FLOAT_EQ(  1.0f, b[0] );
    EXPECT_FLOAT_EQ( -2.0f, b[1] );
    EXPECT_FLOAT_EQ(  0.2f, b[2] );
    EXPECT_FLOAT_EQ(  3.5f, b[3] );
}

TEST(Math, Vector4_ConstIndexOperatorRead)
{
    const Vec4 v( 1.0f, -2.0f, 0.2f, 3.5f );

    EXPECT_FLOAT_EQ(  1.0f, v[0] );
    EXPECT_FLOAT_EQ( -2.0f, v[1] );
    EXPECT_FLOAT_EQ(  0.2f, v[2] );
    EXPECT_FLOAT_EQ(  3.5f, v[3] );
}

TEST(Math, Vector4_IndexOperatorWrite)
{
    Vec4 v( 1.0f, -2.0f, 0.2f, 3.5f );

    v[0] = 2.0f;
    v[1] = 0.2f;
    v[2] = -1.0f;
    v[3] = -2.5f;

    EXPECT_EQ( Vec4( 2.0f, 0.2f, -1.0f, -2.5f ), v );
}

TEST(Math, Vector4_ConstPointerAccess)
{
    Vec4 v( 1.0f, 2.0f, 3.0f, 7.5f );
    const float * ptr = v.ptr();

    EXPECT_FLOAT_EQ( 1.0f, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0f, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0f, ptr[2] );
    EXPECT_FLOAT_EQ( 7.5f, ptr[3] );
}

TEST(Math, Vector4_ConstConstPointerAccess)
{
    Vec4 v( 1.0f, 2.0f, 3.0f, 7.5f );
    const float * ptr = v.const_ptr();

    EXPECT_FLOAT_EQ( 1.0f, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0f, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0f, ptr[2] );
    EXPECT_FLOAT_EQ( 7.5f, ptr[3] );
}

TEST(Math, Vector4_NonConstPointerReadAndWrite)
{
    Vec4 v( 1.0f, 2.0f, 3.0f, 7.5f );
    float * ptr = v.ptr();

    EXPECT_EQ( Vec4( 1.0f, 2.0f, 3.0f, 7.5f ), v );

    ptr[0] = 5.0f;
    ptr[1] = 6.0f;
    ptr[2] = 7.0f;
    ptr[3] = 9.2f;

    EXPECT_EQ( Vec4( 5.0f, 6.0f, 7.0f, 9.2f ), v );
}

TEST(Math, Vector4_Assignment)
{
    Vec4 a( 1.0f, 2.0f, 3.0f, 0.1f );
    const Vec4 b( 3.0f, 4.0f, 5.0f, 2.2f );
    
    a = b;

    EXPECT_NE( Vec4( 1.0f, 2.0f, 3.0f, 0.1f ), a );
    EXPECT_EQ( Vec4( 3.0f, 4.0f, 5.0f, 2.2f ), a );
}

TEST(Math, Vector4_EqualityOperator)
{
    const Vec4 a( 1.5f, -0.2f, 0.0f, 1.0f );
    const Vec4 b( 1.5f,  0.2f, 0.0f, 0.7f );
    const Vec4 c( 1.5f, -0.2f, 0.1f, 1.0f );
    const Vec4 d( 1.5f,  0.0f,-0.2f, 0.2f );
    const Vec4 e( 0.0f,  1.5f,-0.2f, 0.2f );
    const Vec4 f( 1.5f, -0.2f, 0.0f, 1.0f );

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
    const Vec4 a( 2.2f, -0.333f, 1.5f, 0.0f );
    const Vec4 b( 4.4f/2.0f, -0.999f/3.0f, 0.5f * 3.0f, 0.0f / 1.0f );

    EXPECT_EQ( a, b );
}

TEST(Math, Vector4_InequalityOperator)
{
    const Vec4 a( 1.5f, -0.2f, 0.0f, 1.0f );
    const Vec4 b( 1.5f,  0.2f, 0.0f, 0.7f );
    const Vec4 c( 1.5f, -0.2f, 0.1f, 1.0f );
    const Vec4 d( 1.5f,  0.0f,-0.2f, 0.2f );
    const Vec4 e( 0.0f,  1.5f,-0.2f, 0.2f );
    const Vec4 f( 1.5f, -0.2f, 0.0f, 1.0f );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != d );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}


TEST(Math, Vector4_Negation)
{
    Vec4 a( 2.0f, 0.0f, -1.0f, 3.5f );
    a = -a;

    EXPECT_EQ( Vec4( -2.0f, -0.0f, 1.0f, -3.5f ), a );
    EXPECT_EQ( Vec4( -2.0f,  0.0f, 1.0f, -3.5f ), a );    // close
}

TEST(Math, Vector4_AdditionOperator)
{
    const Vec4 a( 3.0f, 5.0f, 9.0f, 1.0f );
    const Vec4 b(-4.0f, 6.0f, 3.0f, 2.0f );

    EXPECT_EQ( Vec4( -1.0f, 11.0f, 12.0f, 3.0f ), a + b );
}

TEST(Math, Vector4_SelfAdditionOperator)
{
          Vec4 a( 3.0f, 5.0f, 9.0f, 1.0f );
    const Vec4 b(-4.0f, 6.0f, 3.0f, 2.0f );

    a += b;

    EXPECT_EQ( Vec4( -1.0f, 11.0f, 12.0f, 3.0f ), a );
}

TEST(Math, Vector4_SubtractionOperator)
{
    const Vec4 a( 5.0f, 2.0f, -4.0f,  0.0f );
    const Vec4 b(-1.0f, 3.0f,  8.0f, -2.0f );
    const Vec4 c = a - b;
    
    EXPECT_EQ( Vec4( 6.0f, -1.0f, -12.0f, 2.0f ), c );
}

TEST(Math, Vector4_SelfSubtractionOperator)
{
          Vec4 a( 5.0f, 2.0f, -4.0f,  0.0f );
    const Vec4 b(-1.0f, 3.0f,  8.0f, -2.0f );
    a -= b;
 
    EXPECT_EQ( Vec4( 6.0f, -1.0f, -12.0f, 2.0f ), a );
}

TEST(Math, Vector4_MultiplyOperator)
{
    const Vec4 a( 3.0f, 5.0f, 9.0f, 3.5f );
    const Vec4 b = a * 2.0f;

    EXPECT_EQ( Vec4( 6.0f, 10.0f, 18.0f, 7.0f ), b );
}

TEST(Math, Vector4_SelfMultiplyOperator)
{
    Vec4 a( 3.0f, 5.0f, 9.0f, 3.5f );
    a *= 2.0f;

    EXPECT_EQ( Vec4( 6.0f, 10.0f, 18.0f, 7.0f ), a );
}

TEST(Math, Vector4_DivisionOperator)
{
    const Vec4 a( 3.0f, 5.0f, 9.0f, 6.0f );
    const Vec4 b = a / 2.0f;

    EXPECT_EQ( Vec4( 1.5f, 2.5f, 4.5f, 3.0f ), b );
}

TEST(Math, Vector4_SelfDivisionOperator)
{
    Vec4 a( 3.0f, 5.0f, 9.0f, 6.0f );
    a /= 2.0f;

    EXPECT_EQ( Vec4( 1.5f, 2.5f, 4.5f, 3. ), a );
}

TEST(Math, Vector4_XAccessor)
{
    Vec4 a( 1.0f, 2.0f, 3.0f, 9.0f );
    Vec4 b( 6.0f, 5.0f, 4.0f, 8.0f );

    EXPECT_FLOAT_EQ( 1.0f, a.x() );
    EXPECT_FLOAT_EQ( 6.0f, b.x() );
}

TEST(Math, Vector4_YAccessor)
{
    Vec4 a( 1.0f, 2.0f, 3.0f, 9.0f );
    Vec4 b( 6.0f, 5.0f, 4.0f, 8.0f );

    EXPECT_FLOAT_EQ( 2.0f, a.y() );
    EXPECT_FLOAT_EQ( 5.0f, b.y() );
}

TEST(Math, Vector4_ZAccessor)
{
    Vec4 a( 1.0f, 2.0f, 3.0f, 9.0f );
    Vec4 b( 6.0f, 5.0f, 4.0f, 8.0f );

    EXPECT_FLOAT_EQ( 3.0f, a.z() );
    EXPECT_FLOAT_EQ( 4.0f, b.z() );
}

TEST(Math, Vector4_WAccessor)
{
    Vec4 a( 1.0f, 2.0f, 3.0f, 9.0f );
    Vec4 b( 6.0f, 5.0f, 4.0f, 8.0f );

    EXPECT_FLOAT_EQ( 9.0f, a.w() );
    EXPECT_FLOAT_EQ( 8.0f, b.w() );
}

TEST(Math, Vector4_ZeroVector)
{
    const Vec4 a = Vec4::ZERO;

    EXPECT_FLOAT_EQ( 0.0f, a[0] );
    EXPECT_FLOAT_EQ( 0.0f, a[1] );
    EXPECT_FLOAT_EQ( 0.0f, a[2] );
    EXPECT_FLOAT_EQ( 0.0f, a[3] );
}

TEST(Math, Vector4_ZeroVectorIsZeroValueConstructed)
{
    const Vec4 a( 0.0f, 0.0f, 0.0f, 0.0f );
    const Vec4 z = Vec4::ZERO;

    EXPECT_EQ( a, z );
}

TEST(Math, Vector4_Length)
{
    const Vec4 a( 1.0f, 2.0f, 3.0f, 4.0f );
    EXPECT_FLOAT_EQ( 5.47722558f, length( a ) );
}

TEST(Math, Vector4_LengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, length( TVector4<float>::ZERO ) );
}

TEST(Math, Vector4_SquaredLength)
{
    const Vec4 a( 1.0f, 2.0f, 3.0f, 4.0f );
    EXPECT_FLOAT_EQ( 30.0f, lengthSquared( a ) );
}

TEST(Math, Vector4_SquareLengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, lengthSquared( TVector4<float>::ZERO ) );
}

TEST(Math, Vector4_Normalization)
{
    const Vec4 a( 3.0f, 1.0f, 2.0f,-4.0f );
    const Vec4 n = normalized( a );

    EXPECT_EQ( Vec4( 0.547722557f, 0.182574186f, 0.365148371f, -0.730296743f), n );
}

TEST(Math, Vector4_Serialization)
{

}
