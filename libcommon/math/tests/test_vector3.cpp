/**
 * Unit tests for templated vector3 class. These tests use float32 for the
 * numeric type, but can be adjusted to double precision.
 */
#include <googletest/googletest.h>
#include <math/vector.h>

TEST(Math, Vector3_DefaultContructor)
{
    const Vec3 v;
    EXPECT_TRUE( true );      // test here just to make sure it compiles
}

TEST(Math, Vector3_SizeTest)
{
    const Vec3 v( 1.0f, 2.0f, 3.0f );
    EXPECT_EQ( sizeof(float) * 3, sizeof(v) );
}

TEST(Math, Vector3_MemoryArrayTest)
{
    // Makes sure that a vector is laid out linearly in memory
    Vec3 v[3];

    v[0] = Vec3( 1.0f, 2.0f, 3.0f );
    v[1] = Vec3( 4.0f, 5.0f, 6.0f );
    v[2] = Vec3( 7.0f, 8.0f, 9.0f );

    const float * pVals = v[0].const_ptr();

    EXPECT_EQ( 1.0f, *(pVals + 0) );
    EXPECT_EQ( 2.0f, *(pVals + 1) );
    EXPECT_EQ( 3.0f, *(pVals + 2) );
    EXPECT_EQ( 4.0f, *(pVals + 3) );
    EXPECT_EQ( 5.0f, *(pVals + 4) );
    EXPECT_EQ( 6.0f, *(pVals + 5) );
    EXPECT_EQ( 7.0f, *(pVals + 6) );
    EXPECT_EQ( 8.0f, *(pVals + 7) );
    EXPECT_EQ( 9.0f, *(pVals + 8) );
}

TEST(Math, Vector3_PointerConstructor)
{
    float values[5] = { 3.0f, 2.0f, 5.0f, -3.0f, 6.0f };
    Vec3 v( &values[1] );

    EXPECT_FLOAT_EQ(  2.0f, v[0] );
    EXPECT_FLOAT_EQ(  5.0f, v[1] );
    EXPECT_FLOAT_EQ( -3.0f, v[2] );
}

TEST(Math, Vector3_ValueConstructor)
{
    const Vec3 v( 1.0f, -2.0f, 0.2f );

    EXPECT_FLOAT_EQ(  1.0f, v[0] );
    EXPECT_FLOAT_EQ( -2.0f, v[1] );
    EXPECT_FLOAT_EQ(  0.2f, v[2] );
}

TEST(Math, Vector3_CopyConstructor)
{
    const Vec3 a( 1.0f, -2.0f, 0.2f );
    const Vec3 b( a );

    EXPECT_FLOAT_EQ(  1.0f, b[0] );
    EXPECT_FLOAT_EQ( -2.0f, b[1] );
    EXPECT_FLOAT_EQ(  0.2f, b[2] );
}

TEST(Math, Vector3_ConstIndexOperatorRead)
{
    const Vec3 v( 1.0f, -2.0f, 0.2f );

    EXPECT_FLOAT_EQ(  1.0f, v[0] );
    EXPECT_FLOAT_EQ( -2.0f, v[1] );
    EXPECT_FLOAT_EQ(  0.2f, v[2] );
}

TEST(Math, Vector3_IndexOperatorWrite)
{
    Vec3 v( 1.0f, -2.0f, 0.2f );

    v[0] = 2.0f;
    v[1] = 0.2f;
    v[2] = -1.0f;

    EXPECT_EQ( Vec3( 2.0f, 0.2f, -1.0f ), v );
}

TEST(Math, Vector3_ConstPointerAccess)
{
    Vec3 v( 1.0f, 2.0f, 3.0f );
    const float * ptr = v.ptr();

    EXPECT_FLOAT_EQ( 1.0f, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0f, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0f, ptr[2] );
}

TEST(Math, Vector3_ConstConstPointerAccess)
{
    Vec3 v( 1.0f, 2.0f, 3.0f );
    const float * ptr = v.const_ptr();

    EXPECT_FLOAT_EQ( 1.0f, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0f, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0f, ptr[2] );
}

TEST(Math, Vector3_NonConstPointerReadAndWrite)
{
    Vec3 v( 1.0f, 2.0f, 3.0f );
    float * ptr = v.ptr();

    EXPECT_EQ( Vec3( 1.0f, 2.0f, 3.0f ), v );

    ptr[0] = 5.0f;
    ptr[1] = 6.0f;
    ptr[2] = 7.0f;

    EXPECT_EQ( Vec3( 5.0f, 6.0f, 7.0f ), v );
}

TEST(Math, Vector3_Assignment)
{
    Vec3 a( 1.0f, 2.0f, 3.0f );
    const Vec3 b( 3.0f, 4.0f, 5.0f );
    
    a = b;

    EXPECT_NE( Vec3( 1.0f, 2.0f, 3.0f ), a );
    EXPECT_EQ( Vec3( 3.0f, 4.0f, 5.0f ), a );
}

TEST(Math, Vector3_EqualityOperator)
{
    const Vec3 a( 1.5f, -0.2f, 0.0f );
    const Vec3 b( 1.5f,  0.2f, 0.0f );
    const Vec3 c( 1.5f, -0.2f, 0.1f );
    const Vec3 d( 1.5f,  0.0f,-0.2f );
    const Vec3 e( 0.0f,  1.5f,-0.2f );
    const Vec3 f( 1.5f, -0.2f, 0.0f );

    EXPECT_EQ( a, f );
    EXPECT_EQ( a, a );
    EXPECT_FALSE( a == b );
    EXPECT_FALSE( a == c );
    EXPECT_FALSE( a == d );
    EXPECT_FALSE( a == e );
    EXPECT_TRUE( a == f );
    EXPECT_TRUE( a == a );
}

TEST(Math, Vector3_EqualityOperatorPrecision)
{
    const Vec3 a( 2.2f, -0.333f, 1.5f );
    const Vec3 b( 4.4f/2.0f, -0.999f/3.0f, 0.5f * 3.0f );

    EXPECT_EQ( a, b );
}

TEST(Math, Vector3_InequalityOperator)
{
    const Vec3 a( 1.5f, -0.2f, 0.0f );
    const Vec3 b( 1.5f,  0.2f, 0.0f );
    const Vec3 c( 1.5f, -0.2f, 0.1f );
    const Vec3 d( 1.5f,  0.0f,-0.2f );
    const Vec3 e( 0.0f,  1.5f,-0.2f );
    const Vec3 f( 1.5f, -0.2f, 0.0f );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != d );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}


TEST(Math, Vector3_Negation)
{
    Vec3 a( 2.0f, 0.0f, -1.0f );
    a = -a;

    EXPECT_EQ( Vec3( -2.0f, -0.0f, 1.0f ), a );
    EXPECT_EQ( Vec3( -2.0f,  0.0f, 1.0f ), a );    // close
}

TEST(Math, Vector3_AdditionOperator)
{
    const Vec3 a( 3.0f, 5.0f, 9.0f );
    const Vec3 b(-4.0f, 6.0f, 3.0f );

    EXPECT_EQ( Vec3( -1.0f, 11.0f, 12.0f ), a + b );
}

TEST(Math, Vector3_SelfAdditionOperator)
{
          Vec3 a( 3.0f, 5.0f, 9.0f );
    const Vec3 b(-4.0f, 6.0f, 3.0f );

    a += b;

    EXPECT_EQ( Vec3( -1.0f, 11.0f, 12.0f ), a );
}

TEST(Math, Vector3_SubtractionOperator)
{
    const Vec3 a( 5.0f, 2.0f, -4.0f );
    const Vec3 b(-1.0f, 3.0f,  8.0f );
    const Vec3 c = a - b;
    
    EXPECT_EQ(   6.0f, c[0] );
    EXPECT_EQ(  -1.0f, c[1] );
    EXPECT_EQ( -12.0f, c[2] );
}

TEST(Math, Vector3_SelfSubtractionOperator)
{
    Vec3       a( 5.0f, 2.0f, -4.0f );
    const Vec3 b(-1.0f, 3.0f,  8.0f );
    a -= b;
    
    EXPECT_EQ(   6.0f, a[0] );
    EXPECT_EQ(  -1.0f, a[1] );
    EXPECT_EQ( -12.0f, a[2] );
}

TEST(Math, Vector3_MultiplyOperator)
{
    const Vec3 a( 3.0f, 5.0f, 9.0f );
    const Vec3 b = a * 2.0f;

    EXPECT_EQ( Vec3( 6.0f, 10.0f, 18.0f ), b );
}

TEST(Math, Vector3_SelfMultiplyOperator)
{
    Vec3 a( 3.0f, 5.0f, 9.0f );
    a *= 2.0f;

    EXPECT_EQ( Vec3( 6.0f, 10.0f, 18.0f ), a );
}

TEST(Math, Vector3_DivisionOperator)
{
    const Vec3 a( 3.0f, 5.0f, 9.0f );
    const Vec3 b = a / 2.0f;

    EXPECT_EQ( Vec3( 1.5f, 2.5f, 4.5f ), b );
}

TEST(Math, Vector3_SelfDivisionOperator)
{
    Vec3 a( 3.0f, 5.0f, 9.0f );
    a /= 2.0f;

    EXPECT_EQ( Vec3( 1.5f, 2.5f, 4.5f ), a );
}

TEST(Math, Vector3_XAccessor)
{
    Vec3 a( 1.0f, 2.0f, 3.0f );
    Vec3 b( 6.0f, 5.0f, 4.0f );

    EXPECT_EQ( 1.0f, a.x() );
    EXPECT_EQ( 6.0f, b.x() );
}

TEST(Math, Vector3_YAccessor)
{
    Vec3 a( 1.0f, 2.0f, 3.0f );
    Vec3 b( 6.0f, 5.0f, 4.0f );

    EXPECT_EQ( 2.0f, a.y() );
    EXPECT_EQ( 5.0f, b.y() );
}

TEST(Math, Vector3_ZAccessor)
{
    Vec3 a( 1.0f, 2.0f, 3.0f );
    Vec3 b( 6.0f, 5.0f, 4.0f );

    EXPECT_EQ( 3.0f, a.z() );
    EXPECT_EQ( 4.0f, b.z() );
}

TEST(Math, Vector3_ZeroVector)
{
    const Vec3 a = Vec3::ZERO;

    EXPECT_EQ( a[0], 0.0f );
    EXPECT_EQ( a[1], 0.0f );
    EXPECT_EQ( a[2], 0.0f );
}

TEST(Math, Vector3_ZeroVectorIsZeroValueConstructed)
{
    const Vec3 a( 0.0f, 0.0f, 0.0f );
    const Vec3 z = Vec3::ZERO;

    EXPECT_EQ( a, z );
}

TEST(Math, Vector3_CrossProductZero)
{
    EXPECT_EQ( Vec3::ZERO, cross( Vec3::ZERO, Vec3( 1.0f, 2.0f, 3.0f ) ) );
}

TEST(Math, Vector3_CrossProduct)
{
    const Vec3 a( 1.0f, 3.0f, -4.0f );
    const Vec3 b( 2.0f, -5.0f, 8.0f );
    const Vec3 r( 4.0f, -16.0f, -11.0f );

    EXPECT_EQ( r, cross( a, b ) );
}

TEST(Math, Vector3_SimpleDotProduct2D)
{
    const Vec3 a( 60, 80, 0 );
    const Vec3 b( 30, 40, 0 );

    EXPECT_EQ( 5000.0f, dot( a, b ) );
}

TEST(Math, Vector3_SimpleDotProduct3D)
{
    const Vec3 a( 60, 80, 100 );
    const Vec3 b( 30, 40, 50 );

    EXPECT_EQ( 10000.0f, dot( a, b ) );
}

TEST(Math, Vector3_DotOppositeIsNegative)
{
    // Tests axiom that dot product of opposite vectors is the
    // negative
    const Vec3 a( 60, 80, 100 );
    const Vec3 b( 30, 40, 50 );
    const Vec3 c( -30, -40, -50 );

    EXPECT_EQ( -1 * dot(a,b), dot(a,c) );
}

TEST(Math, Vector3_DotSameOrientIsLengthMul)
{
    // Tests axiom that dot product of two vectors with the same
    // oriention is the product of their lengths
    const Vec3 a( 2.0f, 2.0f, 2.0f );
    const Vec3 b( 4.0f, 4.0f, 4.0f );

    float dotVal = dot( a, b );
    float lenVal = length( a ) * length( b );

    EXPECT_FLOAT_EQ( dotVal, lenVal );
}

TEST(Math, Vector3_PerpendicularDotsAreZero)
{
    const Vec3 a( 25.0f, 50.0f, -25.0f );
    const Vec3 b( -125.0f, 50.0f, -25.0f );

    EXPECT_EQ( dot( a, b ), 0.0f );
    EXPECT_FLOAT_EQ( 90.0f, angleBetween( a, b ) );
}

TEST(Math, Vector3_Length)
{
    const Vec3 a( 1.0f, 2.0f, 3.0f );
    EXPECT_FLOAT_EQ( 3.741657f, length( a ) );
}

TEST(Math, Vector3_LengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, length( TVector3<float>::ZERO ) );
}

TEST(Math, Vector3_SquaredLength)
{
    const Vec3 a( 1.0f, 2.0f, 3.0f );
    EXPECT_EQ( 14.0f, lengthSquared( a ) );
}

TEST(Math, Vector3_SquareLengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, lengthSquared( TVector3<float>::ZERO ) );
}

TEST(Math, Vector3_AngleBetween)
{
    Vec3 a( 3.0f,  5.0f, 6.0f );
    Vec3 b( 1.0f, -2.0f, 4.0f );

    EXPECT_FLOAT_EQ( 63.679333f, angleBetween( a, b ) );
}

TEST(Math, Vector3_Normalization)
{
    const Vec3 a( 3.0f, 1.0f, 2.0f );
    const Vec3 n = normalized( a );

    EXPECT_EQ( Vec3( 0.801784f, 0.267261f, 0.534522f ), n );
}

TEST(Math, Vector3_RotateAroundXZero)
{
    const Vec3 a( 4.0f, -5.0f, 2.5f );
    EXPECT_EQ( a, rotateAroundX( a, 0.0f ) );
}

TEST(Math, Vector3_RotateAroundX)
{
    // First trial
    const Vec3 a( 0.0f, 1.0f, 0.0f );
    EXPECT_EQ( Vec3( 0.0f,  0.707106f,  0.707106f ), rotateAroundX( a, 45.0f ) );
    EXPECT_EQ( Vec3( 0.0f,  0.0f,       1.0f ),      rotateAroundX( a, 90.0f ) );
    EXPECT_EQ( Vec3( 0.0f, -1.0f,       0.0f ),      rotateAroundX( a, 180.0f ) );
    EXPECT_EQ( Vec3( 0.0f, -0.707106f, -0.707106f ), rotateAroundX( a, 225.0f ) );
    EXPECT_EQ( Vec3( 0.0f,  0.0f,      -1.0f ),      rotateAroundX( a, 270.0f ) );
    EXPECT_EQ( Vec3( 0.0f,  0.707106f, -0.707106f ), rotateAroundX( a, 315.0f ) );

    // Second trial... moving shouldn't efect rotation at all
    const Vec3 b( 2.0f, 1.0f, 0.0f );
    EXPECT_EQ( Vec3( 2.0f,  0.707106f,  0.707106f ), rotateAroundX( b, 45.0f ) );
    EXPECT_EQ( Vec3( 2.0f,  0.0f,       1.0f ),      rotateAroundX( b, 90.0f ) );
    EXPECT_EQ( Vec3( 2.0f, -1.0f,       0.0f ),      rotateAroundX( b, 180.0f ) );
    EXPECT_EQ( Vec3( 2.0f, -0.707106f, -0.707106f ), rotateAroundX( b, 225.0f ) );
    EXPECT_EQ( Vec3( 2.0f,  0.0f,      -1.0f ),      rotateAroundX( b, 270.0f ) );
    EXPECT_EQ( Vec3( 2.0f,  0.707106f, -0.707106f ), rotateAroundX( b, 315.0f ) );
}

TEST(Math, Vector3_RotateAroundYZero)
{
    const Vec3 a( 4.0f, -5.0f, 2.5f );
    EXPECT_EQ( a, rotateAroundY( a, 0.0f ) );
}

TEST(Math, Vector3_RotateAroundY)
{
}

TEST(Math, Vector3_RotateAroundZZero)
{
    const Vec3 a( 4.0f, -5.0f, 2.5f );
    EXPECT_EQ( a, rotateAroundZ( a, 0.0f ) );
}

TEST(Math, Vector3_RotateAroundAxisZero)
{
    const Vec3 a( 4.0f, -5.0f, 2.5f );
    EXPECT_EQ( a, rotateAround( a, Vec3( 1.0f, 1.0f, 1.0f ), 0.0f ) );
}
