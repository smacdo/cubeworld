#include <googletest/googletest.h>
#include <common/utils.h>

TEST(UtilsTests,Begin)
{
    int a[3] = { 5, 6, 7 };

    EXPECT_EQ( &a[0], begin(a) );
}

TEST(UtilsTests,End)
{
    int a[3] = { 5, 6, 7 };
    EXPECT_EQ( &a[0] + 3, end(a) );
}
