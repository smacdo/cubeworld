/**
 * Unit tests for templated vector3 class. These tests use float32 for the
 * numeric type, but can be adjusted to double precision.
 */
#include <googletest/googletest.h>
#include <math/quaternion.h>
#include <cmath>

TEST(Math, Quaternion_DefaultContructor)
{
    const Quat q;
    EXPECT_TRUE( true );      // test here just to make sure it compiles
}

TEST(Math, Quaternion_SizeTest)
{
    // Verify that the quaternion is 16 bytes in size (4 * 4)
    const Quat q( 1.0f, 2.0f, 3.0f, 4.0f );
    EXPECT_EQ( 16u, sizeof(q) );
}

TEST(Math, Quaternion_ValueConstructor)
{
    Quat q( 3.0f, 2.0f, -4.0f, 6.0f );

    EXPECT_FLOAT_EQ(  3.0f, q.w() );
    EXPECT_FLOAT_EQ(  2.0f, q.x() );
    EXPECT_FLOAT_EQ( -4.0f, q.y() );
    EXPECT_FLOAT_EQ(  6.0f, q.z() );
}

TEST(Math, Quaternion_CopyConstructor)
{
    const Quat a( 1.0f, -2.0f, 0.2f, 3.5f );
    const Quat q( a );

    EXPECT_FLOAT_EQ(  1.0f, q.w() );
    EXPECT_FLOAT_EQ( -2.0f, q.x() );
    EXPECT_FLOAT_EQ(  0.2f, q.y() );
    EXPECT_FLOAT_EQ(  3.5f, q.z() );
}

TEST(Math, Quaternion_ConstIndexOperatorRead)
{
    const Quat q( 1.0f, -2.0f, 0.2f, 3.5f );

    EXPECT_FLOAT_EQ(  1.0f, q[0] );
    EXPECT_FLOAT_EQ( -2.0f, q[1] );
    EXPECT_FLOAT_EQ(  0.2f, q[2] );
    EXPECT_FLOAT_EQ(  3.5f, q[3] );
}

TEST(Math, Quaternion_IndexOperatorWrite)
{
    Quat q( 1.0f, -2.0f, 0.2f, 3.5f );

    q[0] =  2.0f;
    q[1] =  0.2f;
    q[2] = -1.0f;
    q[3] =  2.5f;

    EXPECT_FLOAT_EQ(  2.0f, q.w() );
    EXPECT_FLOAT_EQ(  0.2f, q.x() );
    EXPECT_FLOAT_EQ( -1.0f, q.y() );
    EXPECT_FLOAT_EQ(  2.5f, q.z() );

}

TEST(Math, Quaternion_Assignment)
{
    Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat b( 3.0f, 4.0f, 5.0f, 6.0f );
    
    a = b;

    EXPECT_NE( Quat( 1.0f, 2.0f, 3.0f, 4.0f ), a );
    EXPECT_EQ( Quat( 3.0f, 4.0f, 5.0f, 6.0f ), a );
}

TEST(Math, Quaternion_Equality)
{
    const Quat a( 1.5f, -0.2f, 0.0f, 1.0f );
    const Quat b( 1.5f,  0.2f, 0.0f, 0.7f );
    const Quat c( 1.5f, -0.2f, 0.1f, 1.0f );
    const Quat d( 1.5f,  0.0f,-0.2f, 0.2f );
    const Quat e( 0.0f,  1.5f,-0.2f, 0.2f );
    const Quat f( 1.5f, -0.2f, 0.0f, 1.0f );

    EXPECT_EQ( a, f );
    EXPECT_EQ( a, a );
    EXPECT_FALSE( a == b );
    EXPECT_FALSE( a == c );
    EXPECT_FALSE( a == d );
    EXPECT_FALSE( a == e );
    EXPECT_TRUE( a == f );
    EXPECT_TRUE( a == a );
}

TEST(Math, Quaternion_Inequality)
{
    const Quat a( 1.5f, -0.2f, 0.0f, 1.0f );
    const Quat b( 1.5f,  0.2f, 0.0f, 0.7f );
    const Quat c( 1.5f, -0.2f, 0.1f, 1.0f );
    const Quat d( 1.5f,  0.0f,-0.2f, 0.2f );
    const Quat e( 0.0f,  1.5f,-0.2f, 0.2f );
    const Quat f( 1.5f, -0.2f, 0.0f, 1.0f );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != d );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}

TEST(Math, Quaternion_Addition)
{
    const Quat a(  1.0f, 2.0f, 3.0f,  4.0f );
    const Quat b( -1.5f, 2.5f, 3.5f, -4.2f );
    const Quat r = a + b;

    EXPECT_EQ( Quat( -0.5f, 4.5f, 6.5f, -0.2f ), r );
}

TEST(Math, Quaternion_SelfAddition)
{
    const Quat a(  1.0f, 2.0f, 3.0f,  4.0f );
    const Quat b( -1.5f, 2.5f, 3.5f, -4.2f );

    Quat r  = a;
         r += b;  

    EXPECT_EQ( Quat( -0.5f, 4.5f, 6.5f, -0.2f ), r );
}

TEST(Math, Quaternion_Subtraction)
{
    const Quat a(  1.0f, 2.0f, 3.0f,  4.0f );
    const Quat b( -1.5f, 2.5f, 3.2f, -4.2f );
    const Quat r = a - b;

    EXPECT_EQ( Quat( 2.5f, -0.5f, -0.2f, 8.2f ), r );
}

TEST(Math, Quaternion_SelfSubtraction)
{
    const Quat a(  1.0f, 2.0f, 3.0f,  4.0f );
    const Quat b( -1.5f, 2.5f, 3.2f, -4.2f );

    Quat r  = a;
         r -= b;

    EXPECT_EQ( Quat( 2.5f, -0.5f, -0.2f, 8.2f ), r );
}


TEST(Math, Quaternion_Multiply)
{
    const Quat a(  1.0f, 2.0f, 3.0f,  4.0f );
    const Quat b( -1.5f, 2.5f, 3.5f, -4.5f );
    const Quat r = a * b;

    EXPECT_EQ( Quat( 1.0f, -28.0f, 18.0f, -11.0f ), r );
}

TEST(Math, Quaternion_SelfMultiply)
{
    const Quat a(  1.0f, 2.0f, 3.0f,  4.0f );
    const Quat b( -1.5f, 2.5f, 3.5f, -4.5f );

    Quat r  = a;
         r *= b;  

    EXPECT_EQ( Quat( 1.0f, -28.0f, 18.0f, -11.0f ), r );
}

TEST(Math, Quaternion_X)
{
    const Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat b( 1.5f, 2.5f, 3.5f, 4.5f );

    EXPECT_FLOAT_EQ( 2.0f, a.x() );
    EXPECT_FLOAT_EQ( 2.5f, b.x() );
}

TEST(Math, Quaternion_Y)
{
    const Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat b( 1.5f, 2.5f, 3.5f, 4.5f );

    EXPECT_FLOAT_EQ( 3.0f, a.y() );
    EXPECT_FLOAT_EQ( 3.5f, b.y() );
}

TEST(Math, Quaternion_Z)
{
    const Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat b( 1.5f, 2.5f, 3.5f, 4.5f );

    EXPECT_FLOAT_EQ( 4.0f, a.z() );
    EXPECT_FLOAT_EQ( 4.5f, b.z() );
}

TEST(Math, Quaternion_W)
{
    const Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat b( 1.5f, 2.5f, 3.5f, 4.5f );

    EXPECT_FLOAT_EQ( 1.0f, a.w() );
    EXPECT_FLOAT_EQ( 1.5f, b.w() );
}

TEST(Math,Quaternion_Normal)
{
    const Quat q( 1.0f, 2.0f, 3.0f, 4.0f );

    // norm of quaternion[ 1+2i+3j+4k ]
    EXPECT_FLOAT_EQ( sqrtf( 30.0f ), normal( q ) );
}

TEST(Math,Quaternion_Conjugate)
{
    const Quat q( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat c = conjugate( q );

    // conjugate of quaternion[ 1+2i+3j+4k ]
    EXPECT_EQ( Quat( 1.0f, -2.0f, -3.0f, -4.0f ), c );
}

TEST(Math,Quaternion_Inverse)
{
    const Quat q( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat c = inverse( q );

    // conjugate of quaternion[ 1+2i+3j+4k ]
    EXPECT_EQ( Quat( 1.0f, -2.0f, -3.0f, -4.0f ), c );
}

TEST(Math,Quaternion_Unit)
{
    const Quat q( 1.0f, 2.0f, 3.0f, 4.0f );
    const Quat r = normalize( q );

    EXPECT_EQ( Quat( 1.0f / sqrtf( 30.0f ),
                     sqrtf( 2.0f / 15.0f ),
                     sqrtf( 3.0f / 10.0f ),
                     2.0f * sqrtf( 2.0f / 15.0f ) ),
                r );
                    
}

TEST(Math, Quaternion_Zero)
{
    const Quat q = Quat::ZERO;

    EXPECT_FLOAT_EQ( q.x(), 0.0f );
    EXPECT_FLOAT_EQ( q.y(), 0.0f );
    EXPECT_FLOAT_EQ( q.z(), 0.0f );
    EXPECT_FLOAT_EQ( q.w(), 0.0f );
}

TEST(Math, Quaternion_Identity)
{
    const Quat q = Quat::IDENTITY;

    EXPECT_FLOAT_EQ( q.x(), 0.0f );
    EXPECT_FLOAT_EQ( q.y(), 0.0f );
    EXPECT_FLOAT_EQ( q.z(), 0.0f );
    EXPECT_FLOAT_EQ( q.w(), 1.0f );
}
