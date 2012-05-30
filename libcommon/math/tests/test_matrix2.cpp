/**
 * Unit test for templated matrix 2x2
 */
#include <googletest/googletest.h>
#include <math/matrix.h>

const float DELTA = 0.00001;
/*
TEST(Math,Matrix_2x2_NoValueCtor)
{
    Mat2 m();
    EXPECT_TRUE( true );    // no checks, just here to make sure compile
}

TEST(Math,Matrix_2x2_ValueCtor)
{
    Mat2 m( 2.0, 4.0, 
            1.2, 3.0 );

    EXPECT_FLOAT_EQ( 2.0, m.at(0,0) );
    EXPECT_FLOAT_EQ( 4.0, m.at(0,1) );
    EXPECT_FLOAT_EQ( 1.2, m.at(1,0) );
    EXPECT_FLOAT_EQ( 3.0, m.at(1,1) );
}

TEST(Math,Matrix_2x2_ArrayCtor)
{
    float vals[] = { 2.0, 1.2, 4.0, 3.0 };

    Mat2 m( (float*) &vals[0] );

    EXPECT_FLOAT_EQ( 2.0, m.at(0,0) );
    EXPECT_FLOAT_EQ( 4.0, m.at(0,1) );
    EXPECT_FLOAT_EQ( 1.2, m.at(1,0) );
    EXPECT_FLOAT_EQ( 3.0, m.at(1,1) );
}

TEST(Math,Matrix_2x2_CopyCtor)
{
    Mat2 m( -42.0, 35.0,
                34.0, 1.2 );
    Mat2 c( m );

    EXPECT_EQ( m, c );
}

TEST(Math,Matrix_2x2_Assignment)
{
    Mat2 m( 2.0, 4.0, 
            1.2, 3.0 );
    Mat2 b;
    
    EXPECT_NE( b, m );

    b = m;

    EXPECT_EQ( b, m );
}

TEST(Math,Matrix_2x2_Addition)
{
    Mat2 a(  3.2, -0.0,
            -1.0,  2.0 );
    Mat2 b(  1.1, -2.0,
                1.0,  1.2 );
    Mat2 v(  4.3, -2.0,
                0.0,  3.2 );

    EXPECT_EQ( v, (a+b) );
}

TEST(Math,Matrix_2x2_SelfAddition)
{
    Mat2 a(  3.2, -0.0,
            -1.0,  2.0 );
    Mat2 b(  1.1, -2.0,
                1.0,  1.2 );
    Mat2 v(  4.3, -2.0,
                0.0,  3.2 );

    a += b;

    EXPECT_EQ( v, a );
    EXPECT_NE( v, b );
    EXPECT_NE( a, b );
}

TEST(Math,Matrix_2x2_Subtraction)
{
    Mat2 a(  3.2, -2.0,
            -1.0,  2.0 );
    Mat2 b(  1.1,  0.0,
            -1.0,  1.2 );
    Mat2 v(  2.1, -2.0,
                0.0,  0.8 );

    EXPECT_EQ( (a-b), v );
}

TEST(Math,Matrix_2x2_SelfSubtraction)
{
    Mat2 a(  3.2, -2.0,
            -1.0,  2.0 );
    Mat2 b(  1.1,  0.0,
            -1.0,  1.2 );
    Mat2 v(  2.1, -2.0,
                0.0,  0.8 );

    a -= b;

    EXPECT_EQ( v, a );
    EXPECT_NE( a, b );
    EXPECT_NE( v, b );
}

TEST(Math,Matrix_2x2_SelfEquality)
{
    Mat2 a;

    EXPECT_EQ( a, a );
}

TEST(Math,Matrix_2x2_Equality)
{
    Mat2 m( 2.0, 4.0, 
            1.2, 3.0 );
    Mat2 n( m );

    EXPECT_EQ( m, n );
    EXPECT_FALSE( m != n );

    // sanity
    n = ( m + n );

    EXPECT_FALSE( m == n );
}

TEST(Math,Matrix_2x2_SelfInequalityFalse)
{
    Mat2 m;

    EXPECT_FALSE( m != m );
}

TEST(Math,Matrix_2x2_Inequality)
{
    Mat2 m( 2.0, 4.0, 
            1.2, 3.0 );
    Mat2 n( m );

    EXPECT_FALSE( m != n );
    EXPECT_TRUE( m == n );

    // sanity
    n = m + n;

    EXPECT_TRUE( m != n );
}

TEST(Math,Matrix_2x2_Zero)
{
    Mat2 m( 0.0, 0.0,
            0.0, 0.0 );

    EXPECT_TRUE( m.isZeroMatrix() );
}

TEST(Math,Matrix_2x2_IsIdentity)
{
    Mat2 a( 1.0, 1.0,
            1.0, 0.0 );
    Mat2 b( 1.0, 0.0,
            0.0, 1.0 );

    EXPECT_TRUE(! a.isIdentityMatrix() );
    EXPECT_TRUE(  b.isIdentityMatrix() );
}

TEST(Math,Matrix_2x2_Swap)
{
    Mat2 a( 1.0, 2.0,
            3.0, 4.0 );
    Mat2 b( 5.0, 6.0,
            7.0, 8.0 );

    Mat2 x( a );
    Mat2 y( b );

    // pre-condition (x==a, y==b, x!=y)
    EXPECT_EQ( a, x );
    EXPECT_EQ( b, y );
    EXPECT_NE( x, y );

    // swap and check post condition (x==b, y==a, x!=y)
    swap( x, y );

    EXPECT_EQ( b, x );
    EXPECT_EQ( a, y );
    EXPECT_NE( x, y );
}

*/
