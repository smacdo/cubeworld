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
    const Vec3 v( 1.0, 2.0, 3.0 );
    EXPECT_EQ( sizeof(float) * 3, sizeof(v) );
}

TEST(Math, Vector3_MemoryArrayTest)
{
    // Makes sure that a vector is laid out linearly in memory
    Vec3 v[3];

    v[0] = Vec3( 1.0, 2.0, 3.0 );
    v[1] = Vec3( 4.0, 5.0, 6.0 );
    v[2] = Vec3( 7.0, 8.0, 9.0 );

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
}

TEST(Math, Vector3_PointerConstructor)
{
    float values[5] = { 3.0, 2.0, 5.0, -3.0, 6.0 };
    Vec3 v( &values[1] );

    EXPECT_FLOAT_EQ(  2.0, v[0] );
    EXPECT_FLOAT_EQ(  5.0, v[1] );
    EXPECT_FLOAT_EQ( -3.0, v[2] );
}

TEST(Math, Vector3_ValueConstructor)
{
    const Vec3 v( 1.0, -2.0, 0.2 );

    EXPECT_FLOAT_EQ(  1.0, v[0] );
    EXPECT_FLOAT_EQ( -2.0, v[1] );
    EXPECT_FLOAT_EQ(  0.2, v[2] );
}

TEST(Math, Vector3_CopyConstructor)
{
    const Vec3 a( 1.0, -2.0, 0.2 );
    const Vec3 b( a );

    EXPECT_FLOAT_EQ(  1.0, b[0] );
    EXPECT_FLOAT_EQ( -2.0, b[1] );
    EXPECT_FLOAT_EQ(  0.2, b[2] );
}

TEST(Math, Vector3_ConstIndexOperatorRead)
{
    const Vec3 v( 1.0, -2.0, 0.2 );

    EXPECT_FLOAT_EQ(  1.0, v[0] );
    EXPECT_FLOAT_EQ( -2.0, v[1] );
    EXPECT_FLOAT_EQ(  0.2, v[2] );
}

TEST(Math, Vector3_IndexOperatorWrite)
{
    Vec3 v( 1.0, -2.0, 0.2 );

    v[0] = 2.0;
    v[1] = 0.2;
    v[2] = -1.0;

    EXPECT_EQ( Vec3( 2.0, 0.2, -1.0 ), v );
}

TEST(Math, Vector3_ConstPointerAccess)
{
    Vec3 v( 1.0, 2.0, 3.0 );
    const float * ptr = v.ptr();

    EXPECT_FLOAT_EQ( 1.0, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0, ptr[2] );
}

TEST(Math, Vector3_ConstConstPointerAccess)
{
    Vec3 v( 1.0, 2.0, 3.0 );
    const float * ptr = v.const_ptr();

    EXPECT_FLOAT_EQ( 1.0, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0, ptr[1] );
    EXPECT_FLOAT_EQ( 3.0, ptr[2] );
}

TEST(Math, Vector3_NonConstPointerReadAndWrite)
{
    Vec3 v( 1.0, 2.0, 3.0 );
    float * ptr = v.ptr();

    EXPECT_EQ( Vec3( 1.0, 2.0, 3.0 ), v );

    ptr[0] = 5.0;
    ptr[1] = 6.0;
    ptr[2] = 7.0;

    EXPECT_EQ( Vec3( 5.0, 6.0, 7.0 ), v );
}

TEST(Math, Vector3_Assignment)
{
    Vec3 a( 1.0, 2.0, 3.0 );
    const Vec3 b( 3.0, 4.0, 5.0 );
    
    a = b;

    EXPECT_NE( Vec3( 1.0, 2.0, 3.0 ), a );
    EXPECT_EQ( Vec3( 3.0, 4.0, 5.0 ), a );
}

TEST(Math, Vector3_EqualityOperator)
{
    const Vec3 a( 1.5, -0.2, 0.0 );
    const Vec3 b( 1.5,  0.2, 0.0 );
    const Vec3 c( 1.5, -0.2, 0.1 );
    const Vec3 d( 1.5,  0.0,-0.2 );
    const Vec3 e( 0.0,  1.5,-0.2 );
    const Vec3 f( 1.5, -0.2, 0.0 );

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
    const Vec3 a( 2.2, -0.333, 1.5 );
    const Vec3 b( 4.4/2.0, -0.999/3.0, 0.5 * 3.0 );

    EXPECT_EQ( a, b );
}

TEST(Math, Vector3_InequalityOperator)
{
    const Vec3 a( 1.5, -0.2, 0.0 );
    const Vec3 b( 1.5,  0.2, 0.0 );
    const Vec3 c( 1.5, -0.2, 0.1 );
    const Vec3 d( 1.5,  0.0,-0.2 );
    const Vec3 e( 0.0,  1.5,-0.2 );
    const Vec3 f( 1.5, -0.2, 0.0 );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != d );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}


TEST(Math, Vector3_Negation)
{
    Vec3 a( 2.0, 0.0, -1.0 );
    a = -a;

    EXPECT_EQ( Vec3( -2.0, -0.0, 1.0 ), a );
    EXPECT_EQ( Vec3( -2.0,  0.0, 1.0 ), a );    // close
}

TEST(Math, Vector3_AdditionOperator)
{
    const Vec3 a( 3.0, 5.0, 9.0 );
    const Vec3 b(-4.0, 6.0, 3.0 );

    EXPECT_EQ( Vec3( -1.0, 11.0, 12.0 ), a + b );
}

TEST(Math, Vector3_SelfAdditionOperator)
{
          Vec3 a( 3.0, 5.0, 9.0 );
    const Vec3 b(-4.0, 6.0, 3.0 );

    a += b;

    EXPECT_EQ( Vec3( -1.0, 11.0, 12.0 ), a );
}

TEST(Math, Vector3_SubtractionOperator)
{
    const Vec3 a( 5.0, 2.0, -4.0 );
    const Vec3 b(-1.0, 3.0,  8.0 );
    const Vec3 c = a - b;
    
    EXPECT_EQ(   6.0, c[0] );
    EXPECT_EQ(  -1.0, c[1] );
    EXPECT_EQ( -12.0, c[2] );
}

TEST(Math, Vector3_SelfSubtractionOperator)
{
    Vec3       a( 5.0, 2.0, -4.0 );
    const Vec3 b(-1.0, 3.0,  8.0 );
    a -= b;
    
    EXPECT_EQ(   6.0, a[0] );
    EXPECT_EQ(  -1.0, a[1] );
    EXPECT_EQ( -12.0, a[2] );
}

TEST(Math, Vector3_MultiplyOperator)
{
    const Vec3 a( 3.0, 5.0, 9.0 );
    const Vec3 b = a * 2.0;

    EXPECT_EQ( Vec3( 6.0, 10.0, 18.0 ), b );
}

TEST(Math, Vector3_SelfMultiplyOperator)
{
    Vec3 a( 3.0, 5.0, 9.0 );
    a *= 2.0;

    EXPECT_EQ( Vec3( 6.0, 10.0, 18.0 ), a );
}

TEST(Math, Vector3_DivisionOperator)
{
    const Vec3 a( 3.0, 5.0, 9.0 );
    const Vec3 b = a / 2.0;

    EXPECT_EQ( Vec3( 1.5, 2.5, 4.5 ), b );
}

TEST(Math, Vector3_SelfDivisionOperator)
{
    Vec3 a( 3.0, 5.0, 9.0 );
    a /= 2.0;

    EXPECT_EQ( Vec3( 1.5, 2.5, 4.5 ), a );
}

TEST(Math, Vector3_XAccessor)
{
    Vec3 a( 1.0, 2.0, 3.0 );
    Vec3 b( 6.0, 5.0, 4.0 );

    EXPECT_EQ( 1.0, a.x() );
    EXPECT_EQ( 6.0, b.x() );
}

TEST(Math, Vector3_YAccessor)
{
    Vec3 a( 1.0, 2.0, 3.0 );
    Vec3 b( 6.0, 5.0, 4.0 );

    EXPECT_EQ( 2.0, a.y() );
    EXPECT_EQ( 5.0, b.y() );
}

TEST(Math, Vector3_ZAccessor)
{
    Vec3 a( 1.0, 2.0, 3.0 );
    Vec3 b( 6.0, 5.0, 4.0 );

    EXPECT_EQ( 3.0, a.z() );
    EXPECT_EQ( 4.0, b.z() );
}

TEST(Math, Vector3_ZeroVector)
{
    const Vec3 a = Vec3::ZERO;

    EXPECT_EQ( a[0], 0.0 );
    EXPECT_EQ( a[1], 0.0 );
    EXPECT_EQ( a[2], 0.0 );
}

TEST(Math, Vector3_ZeroVectorIsZeroValueConstructed)
{
    const Vec3 a( 0.0, 0.0, 0.0 );
    const Vec3 z = Vec3::ZERO;

    EXPECT_EQ( a, z );
}

TEST(Math, Vector3_CrossProductZero)
{
    EXPECT_EQ( Vec3::ZERO, cross( Vec3::ZERO, Vec3( 1.0, 2.0, 3.0 ) ) );
}

TEST(Math, Vector3_CrossProduct)
{
    const Vec3 a( 1.0, 3.0, -4.0 );
    const Vec3 b( 2.0, -5.0, 8.0 );
    const Vec3 r( 4.0, -16.0, -11.0 );

    EXPECT_EQ( r, cross( a, b ) );
}

TEST(Math, Vector3_SimpleDotProduct2D)
{
    const Vec3 a( 60, 80, 0 );
    const Vec3 b( 30, 40, 0 );

    EXPECT_EQ( 5000.0, dot( a, b ) );
}

TEST(Math, Vector3_SimpleDotProduct3D)
{
    const Vec3 a( 60, 80, 100 );
    const Vec3 b( 30, 40, 50 );

    EXPECT_EQ( 10000.0, dot( a, b ) );
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
    const Vec3 a( 2.0, 2.0, 2.0 );
    const Vec3 b( 4.0, 4.0, 4.0 );

    float dotVal = dot( a, b );
    float lenVal = length( a ) * length( b );

    EXPECT_FLOAT_EQ( dotVal, lenVal );
}

TEST(Math, Vector3_PerpendicularDotsAreZero)
{
    const Vec3 a( 25.0, 50.0, -25.0 );
    const Vec3 b( -125.0, 50.0, -25.0 );

    EXPECT_EQ( dot( a, b ), 0.0f );
    EXPECT_FLOAT_EQ( 90.0f, angleBetween( a, b ) );
}

TEST(Math, Vector3_Length)
{
    const Vec3 a( 1.0, 2.0, 3.0 );
    EXPECT_FLOAT_EQ( 3.741657, length( a ) );
}

TEST(Math, Vector3_LengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, length( TVector3<float>::ZERO ) );
}

TEST(Math, Vector3_SquaredLength)
{
    const Vec3 a( 1.0, 2.0, 3.0 );
    EXPECT_EQ( 14.0, lengthSquared( a ) );
}

TEST(Math, Vector3_SquareLengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, lengthSquared( TVector3<float>::ZERO ) );
}

TEST(Math, Vector3_AngleBetween)
{
    Vec3 a( 3.0,  5.0, 6.0 );
    Vec3 b( 1.0, -2.0, 4.0 );

    EXPECT_FLOAT_EQ( 63.679333f, angleBetween( a, b ) );
}

TEST(Math, Vector3_Normalization)
{
    const Vec3 a( 3.0, 1.0, 2.0 );
    const Vec3 n = normalized( a );

    EXPECT_EQ( Vec3( 0.801784, 0.267261, 0.534522 ), n );
}

TEST(Math, Vector3_RotateAroundXZero)
{
    const Vec3 a( 4.0, -5.0, 2.5 );
    EXPECT_EQ( a, rotateAroundX( a, 0.0f ) );
}

TEST(Math, Vector3_RotateAroundX)
{
    // First trial
    const Vec3 a( 0.0, 1.0, 0.0 );
    EXPECT_EQ( Vec3( 0.0,  0.707106,  0.707106 ), rotateAroundX( a, 45.0f ) );
    EXPECT_EQ( Vec3( 0.0,  0.0,       1.0 ),      rotateAroundX( a, 90.0f ) );
    EXPECT_EQ( Vec3( 0.0, -1.0,       0.0 ),      rotateAroundX( a, 180.0f ) );
    EXPECT_EQ( Vec3( 0.0, -0.707106, -0.707106 ), rotateAroundX( a, 225.0f ) );
    EXPECT_EQ( Vec3( 0.0,  0.0,      -1.0 ),      rotateAroundX( a, 270.0f ) );
    EXPECT_EQ( Vec3( 0.0,  0.707106, -0.707106 ), rotateAroundX( a, 315.0f ) );

    // Second trial... moving shouldn't effect rotation at all
    const Vec3 b( 2.0, 1.0, 0.0 );
    EXPECT_EQ( Vec3( 2.0,  0.707106,  0.707106 ), rotateAroundX( b, 45.0f ) );
    EXPECT_EQ( Vec3( 2.0,  0.0,       1.0 ),      rotateAroundX( b, 90.0f ) );
    EXPECT_EQ( Vec3( 2.0, -1.0,       0.0 ),      rotateAroundX( b, 180.0f ) );
    EXPECT_EQ( Vec3( 2.0, -0.707106, -0.707106 ), rotateAroundX( b, 225.0f ) );
    EXPECT_EQ( Vec3( 2.0,  0.0,      -1.0 ),      rotateAroundX( b, 270.0f ) );
    EXPECT_EQ( Vec3( 2.0,  0.707106, -0.707106 ), rotateAroundX( b, 315.0f ) );
}

TEST(Math, Vector3_RotateAroundYZero)
{
    const Vec3 a( 4.0, -5.0, 2.5 );
    EXPECT_EQ( a, rotateAroundY( a, 0.0f ) );
}

TEST(Math, Vector3_RotateAroundY)
{
}

TEST(Math, Vector3_RotateAroundZZero)
{
    const Vec3 a( 4.0, -5.0, 2.5 );
    EXPECT_EQ( a, rotateAroundZ( a, 0.0f ) );
}

TEST(Math, Vector3_RotateAroundAxisZero)
{
    const Vec3 a( 4.0, -5.0, 2.5 );
    EXPECT_EQ( a, rotateAround( a, Vec3( 1.0, 1.0, 1.0 ), 0.0f ) );
}
