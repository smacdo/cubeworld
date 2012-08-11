/**
 * unit tests for templated matrix 4x4
 * (template type=float)
 */
#include <googletest/googletest.h>
#include <math/matrix.h>

const float DELTA = 0.00001f;

TEST(Math,Matrix4_NoValueCtor)
{
    Mat4 m();
    EXPECT_TRUE( true );   // no checks, just here to make sure compile
}

TEST(Math,Matrix4_ValueCtor)
{
    Mat4 m( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );

    // first row [ 2.0f, 4.0f, 6.0f, 9.0f ]
    EXPECT_FLOAT_EQ( 2.0f, m.at(0,0) );
    EXPECT_FLOAT_EQ( 4.0f, m.at(0,1) );
    EXPECT_FLOAT_EQ( 6.0f, m.at(0,2) );
    EXPECT_FLOAT_EQ( 9.0f, m.at(0,3) );

    // second row [ 1.2f, 3.0f, 5.0f, 7.0f ]
    EXPECT_FLOAT_EQ( 1.2f, m.at(1,0) );
    EXPECT_FLOAT_EQ( 3.0f, m.at(1,1) );
    EXPECT_FLOAT_EQ( 5.0f, m.at(1,2) );
    EXPECT_FLOAT_EQ( 7.0f, m.at(1,3) );

    // third row [ 9.5f, 1.5f, 1.0f, 0.0f ]
    EXPECT_FLOAT_EQ( 9.5f, m.at(2,0) );
    EXPECT_FLOAT_EQ( 1.5f, m.at(2,1) );
    EXPECT_FLOAT_EQ( 1.0f, m.at(2,2) );
    EXPECT_FLOAT_EQ( 0.0f, m.at(2,3) );

    // fourth row [ 2.8f, 9.8f, 6.6f, 8.8f ]
    EXPECT_FLOAT_EQ( 2.8f, m.at(3,0) );
    EXPECT_FLOAT_EQ( 9.8f, m.at(3,1) );
    EXPECT_FLOAT_EQ( 6.6f, m.at(3,2) );
    EXPECT_FLOAT_EQ( 8.8f, m.at(3,3) );
}

TEST(Math,Matrix4_ValuePtrCtor)
{
    float va[16] = { 2.0f, 1.2f, 9.5f, 2.8f,
                     4.0f, 3.0f, 1.5f, 9.8f,
                     6.0f, 5.0f, 1.0f, 6.6f,
                     9.0f, 7.0f, 0.0f, 8.8f };

    Mat4 m( (float*) va );

    // first row
    EXPECT_FLOAT_EQ( 2.0f, m.at(0,0) );
    EXPECT_FLOAT_EQ( 1.2f, m.at(0,1) );
    EXPECT_FLOAT_EQ( 9.5f, m.at(0,2) );
    EXPECT_FLOAT_EQ( 2.8f, m.at(0,3) );

    // second row
    EXPECT_FLOAT_EQ( 4.0f, m.at(1,0) );
    EXPECT_FLOAT_EQ( 3.0f, m.at(1,1) );
    EXPECT_FLOAT_EQ( 1.5f, m.at(1,2) );
    EXPECT_FLOAT_EQ( 9.8f, m.at(1,3) );

    // third row
    EXPECT_FLOAT_EQ( 6.0f, m.at(2,0) );
    EXPECT_FLOAT_EQ( 5.0f, m.at(2,1) );
    EXPECT_FLOAT_EQ( 1.0f, m.at(2,2) );
    EXPECT_FLOAT_EQ( 6.6f, m.at(2,3) );

    // fourth row
    EXPECT_FLOAT_EQ( 9.0f, m.at(3,0) );
    EXPECT_FLOAT_EQ( 7.0f, m.at(3,1) );
    EXPECT_FLOAT_EQ( 0.0f, m.at(3,2) );
    EXPECT_FLOAT_EQ( 8.8f, m.at(3,3) );
}

TEST(Math,Matrix4_CopyCtor)
{
    Mat4 m( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );

    Mat4 r( m );

    EXPECT_EQ( m, r );
}

TEST(Math,Matrix4_Assignment)
{
    Mat4 m( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );
    Mat4 r;
    
    // Make sure empty matrix != value constructed matrix
    EXPECT_NE( m, r );

    // Assign it, then check for equality
    r = m;
    EXPECT_EQ( m, r );
}

TEST(Math,Matrix4_Addition)
{
    // Verified by mathmatica
    // {{3.2f, -0.0f, 4.0f, 2.0f}, {-1.0f,  2.0f, 1.2f, 0.0f}, {3.0f,  1.0f, 7.0f, 2.5f}, {-2.0f,  4.0f, 5.0f, 6.0f}}
    Mat4 a(  3.2f, -0.0f, 4.0f, 2.0f,
            -1.0f,  2.0f, 1.2f, 0.0f,
             3.0f,  1.0f, 7.0f, 2.5f,
            -2.0f,  4.0f, 5.0f, 6.0f );

    // {{1.1f, -2.0f, 1.5f, 3.0f}, {1.0f,  1.2f, 2.2f,-2.2f}, {4.0f,  0.0f, 1.5f, 0.2f}, {1.9f, -4.0f, 2.5f,-1.0f}}
    Mat4 b(  1.1f, -2.0f, 1.5f, 3.0f,
             1.0f,  1.2f, 2.2f,-2.2f,
             4.0f,  0.0f, 1.5f, 0.2f,
             1.9f, -4.0f, 2.5f,-1.0f );

    // {{4.3f, -2., 5.5f, 5.}, {0., 3.2f, 3.4f, -2.2f}, {7., 1., 8.5f, 2.7f}, {-0.1f, 0., 7.5f, 5.}}
    Mat4 v(  4.3f, -2.0f, 5.5f, 5.0f,
             0.0f,  3.2f, 3.4f,-2.2f,
             7.0f,  1.0f, 8.5f, 2.7f,
            -0.1f,  0.0f, 7.5f, 5.0f );

    Mat4 r( a + b );

    EXPECT_EQ( v, r );
}

TEST(Math,Matrix4_SelfAddition)
{
    Mat4 a(  3.2f, -0.0f, 4.0f, 2.0f,
            -1.0f,  2.0f, 1.2f, 0.0f,
             3.0f,  1.0f, 7.0f, 2.5f,
            -2.0f,  4.0f, 5.0f, 6.0f );

    Mat4 b(  1.1f, -2.0f, 1.5f, 3.0f,
             1.0f,  1.2f, 2.2f,-2.2f,
             4.0f,  0.0f, 1.5f, 0.2f,
             1.9f, -4.0f, 2.5f,-1.0f );

    Mat4 v(  4.3f, -2.0f, 5.5f, 5.0f,
             0.0f,  3.2f, 3.4f,-2.2f,
             7.0f,  1.0f, 8.5f, 2.7f,
            -0.1f,  0.0f, 7.5f, 5.0f );

    a += b;

    EXPECT_EQ( a, v );
    EXPECT_NE( b, v );
    EXPECT_NE( a, b );
}

TEST(Math,Matrix4_Subtraction)
{
    Mat4 a(  3.2f, -0.0f, 4.0f, 2.0f,
            -1.0f,  2.0f, 1.2f, 0.0f,
             3.0f,  1.0f, 7.0f, 2.5f,
            -2.0f,  4.0f, 5.0f, 6.0f );

    Mat4 b(  1.1f, -2.0f, 1.5f, 3.0f,
             1.0f,  1.2f, 2.2f,-2.2f,
             4.0f,  0.0f, 1.5f, 0.2f,
             1.9f, -4.0f, 2.5f,-1.0f );

    Mat4 v(  2.1f,  2.0f, 2.5f,-1.0f,
            -2.0f,  0.8f,-1.0f, 2.2f,
            -1.0f,  1.0f, 5.5f, 2.3f,
            -3.9f,  8.0f, 2.5f, 7.0f );

    Mat4 r( a - b );

    EXPECT_EQ( v, r );
}

TEST(Math,Matrix4_SelfSubtraction)
{
    Mat4 a(  3.2f, -0.0f, 4.0f, 2.0f,
            -1.0f,  2.0f, 1.2f, 0.0f,
             3.0f,  1.0f, 7.0f, 2.5f,
            -2.0f,  4.0f, 5.0f, 6.0f );

    Mat4 b(  1.1f, -2.0f, 1.5f, 3.0f,
             1.0f,  1.2f, 2.2f,-2.2f,
             4.0f,  0.0f, 1.5f, 0.2f,
             1.9f, -4.0f, 2.5f,-1.0f );

    Mat4 v(  2.1f,  2.0f, 2.5f,-1.0f,
            -2.0f,  0.8f,-1.0f, 2.2f,
            -1.0f,  1.0f, 5.5f, 2.3f,
            -3.9f,  8.0f, 2.5f, 7.0f );
    a -= b;

    EXPECT_EQ( a, v );
    EXPECT_NE( a, b );
    EXPECT_NE( b, v );
}

TEST(Math,Matrix4_Multiplication)
{
    Mat4 a( 0.0f, 1.0f, 3.0f, 5.0f,
            2.0f, 3.0f, 8.0f, 9.0f,
            3.0f, 4.0f, 1.0f, 2.0f,
            7.0f, 0.0f, 6.0f, 6.0f );

    Mat4 b( 2.0f, 1.0f, 4.0f, 8.0f,
            9.0f, 2.0f, 1.0f, 5.0f,
            7.0f, 6.0f, 6.0f, 7.0f,
            9.0f, 5.0f, 4.0f, 3.0f );

    Mat4 v(  75.0f,  45.0f,  39.0f,  41.0f,
            168.0f, 101.0f,  95.0f, 114.0f,
             67.0f,  27.0f,  30.0f,  57.0f,
            110.0f,  73.0f,  88.0f, 116.0f );

    EXPECT_EQ( v, a * b );
}

TEST(Math,Matrix4_Multiplication2)
{
        Mat4 a(  0.2f,  1.0f,  0.5f, -1.2f,
                 0.6f, -1.4f,  0.0f, -2.0f,
                -0.1f, -1.1f,  0.3f, -0.0f,
                 1.0f,  0.5f,  0.2f,  0.8f );

        Mat4 b(  0.4f,  0.5f,  0.6f, 1.0f,
                 0.2f,  1.0f,  1.5f, 1.2f,
                 0.8f,  1.4f,  0.1f, 0.1f,
                 0.6f,  1.8f,  0.9f, 1.1f );

        Mat4 v(  -1.0f/25.0f,  -9.0f/25.0f,    59.0f/100.0f,   13.0f/100.0f,
                 -31.0f/25.0f, -47.0f/10.0f,  -177.0f/50.0f,  -82.0f/25.0f,
                 -1.0f/50.0f,  -73.0f/100.0f, -42.0f/25.0f,   -139.0f/100.0f,
                  57.0f/50.0f,  68.0f/25.0f,   209.0f/100.0f,  5.0f/2.0f );

        EXPECT_EQ( v, a * b );
}

TEST(Math,Matrix4_Transpose)
{
    Mat4 a(  1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16 );

    Mat4 v(  1,  5,  9, 13,
             2,  6, 10, 14,
             3,  7, 11, 15,
             4,  8, 12, 16 );

    EXPECT_EQ( v, transpose( a ) );
}

TEST(Math,Matrix4_Determinant)
{
    // verified by mathmatica
    // {{6, -7, 10, 2}, {0, 3, -1, 6}, {0, 5, -7, -1}, {3, 6, 1, 4}}
    const Mat4 a( 6.0f, -7.0f, 10.0f,  2.0f,
                  0.0f,  3.0f, -1.0f,  6.0f,
                  0.0f,  5.0f, -7.0f, -1.0f,
                  3.0f,  6.0f,  1.0f,  4.0f );

    EXPECT_FLOAT_EQ( 1371.0f, determinant( a ) );
}

TEST(Math,Matrix4_Inverse)
{
    // verified by mathmatica
    // {{6, -7, 10, 2}, {0, 3, -1, 6}, {0, 5, -7, -1}, {3, 6, 1, 4}}
    const Mat4 a( 6.0f, -7.0f, 10.0f,  2.0f,
                  0.0f,  3.0f, -1.0f,  6.0f,
                  0.0f,  5.0f, -7.0f, -1.0f,
                  3.0f,  6.0f,  1.0f,  4.0f );
   
    // N[Inverse[{{6, -7, 10, 2}, {0, 3, -1, 6}, {0, 5, -7, -1}, {3, 6, 1, 4}}]]
    const Mat4 r(  0.165573f,  -0.0167761f, 0.239241f,   0.00218818f,
                  -0.0940919f, -0.109409f, -0.0919037f,  0.188184f,
                  -0.0722101f, -0.107221f, -0.210066f,   0.14442f,
                   0.0350109f,  0.203501f,  0.0109409f, -0.0700219f );

    EXPECT_EQ( r, inverse( a ) );
}

TEST(Math,Matrix4_SelfEquality)
{
    const Mat4 a( 6.0f, -7.0f, 10.0f,  2.0f,
                  0.0f,  3.0f, -1.0f,  6.0f,
                  0.0f,  5.0f, -7.0f, -1.0f,
                  3.0f,  6.0f,  1.0f,  4.0f );

    EXPECT_EQ( a, a );
}

TEST(Math,Matrix4_Equality)
{
    Mat4 m( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );
    Mat4 n( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );

    EXPECT_EQ( m, n );
    EXPECT_FALSE( m != n );

    // sanity
    n = ( m + n );

    EXPECT_FALSE( m == n );
    EXPECT_TRUE( m != n );
}


TEST(Math,Matrix4_SelfInequalityFalse)
{
    Mat4 m( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );

    EXPECT_FALSE( m != m );
}

TEST(Math,Matrix4_Inequality)
{
    Mat4 m( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );
    Mat4 n( 2.0f, 4.0f, 6.0f, 9.0f, 
            1.2f, 3.0f, 5.0f, 7.0f,
            9.5f, 1.5f, 1.0f, 0.0f,
            2.8f, 9.8f, 6.6f, 8.8f );

    EXPECT_FALSE( (m != n) );
    EXPECT_TRUE ( (m == n) );

    // sanity
    n = m + n;

    EXPECT_NE( m, n );
}

TEST(Math,Matrix4_ZeroMatrix)
{
    Mat4 m( 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f );

    Mat4 n = Mat4::ZERO_MATRIX;

    EXPECT_EQ( m, n );

    EXPECT_TRUE( isZeroMatrix( m ) );
    EXPECT_TRUE( isZeroMatrix( m ) );
}

TEST(Math,Matrix4_MakeIdentityMatrix)
{
    Mat4 a( 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f );
    Mat4 b = Mat4::IDENTITY;

    EXPECT_EQ( a, b );
    EXPECT_TRUE( isIdentityMatrix( a ) );
}

TEST(Math,Matrix4_IsIdentityMatrix)
{
    Mat4 a( 1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f );
    Mat4 b( 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f );

    EXPECT_TRUE(! isIdentityMatrix( a ) );
    EXPECT_TRUE(  isIdentityMatrix( b ) );
}


