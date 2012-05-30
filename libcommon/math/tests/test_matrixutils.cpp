/**
 * Unit tests for matrix utils
 * (template type=float)
 */
#include <googletest/googletest.h>
#include <math/matrix.h>
#include <math/matrixutils.h>

TEST(Math,MatrixUtil_RotationAroundX)
{
    Mat4 m = MatrixUtil::createRotationAroundX<float>( 45.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_RotationAroundY)
{
    Mat4 m = MatrixUtil::createRotationAroundY<float>( 45.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_RotationAroundZ)
{
    Mat4 m = MatrixUtil::createRotationAroundZ<float>( 45.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_RotationAroundAxis)
{
    Mat4 m = MatrixUtil::createRotationAroundAxis( 45.0f, 25.0f, 180.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_Translation)
{
    Mat4 m = MatrixUtil::createTranslation( 45.0f, 5.0f, -6.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_Scale)
{
    Mat4 m = MatrixUtil::createScale( 4.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_LookAt)
{
    Mat4 m = MatrixUtil::createLookAt( Vec3( 2.0f, 5.0f, -8.0f ),
                                       Vec3( 0.0f, 0.0f,  1.0f ),
                                       Vec3( 0.0f, 1.0f,  0.0f ) );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_CreateFrustum)
{
    Mat4 m = MatrixUtil::createFrustum( 30.0f,
                                        55.0f,
                                        10.0f,
                                        75.0f,
                                        00.1f,
                                        736.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_CreateOrtho)
{
    Mat4 m = MatrixUtil::createOrtho( 0.0f, 640.0f,
                                      480.0f, 0.0f,
                                      0.01f,
                                      100.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_CreateRowOrder)
{
    Mat4 m = MatrixUtil::createRowOrder<float>();
    EXPECT_EQ( m, m );
}

TEST(Math,MatrixUtil_CreateColOrder)
{
    Mat4 m = MatrixUtil::createColOrder<float>();
    EXPECT_EQ( m, m );
}
