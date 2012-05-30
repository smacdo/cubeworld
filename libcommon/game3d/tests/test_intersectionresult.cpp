#include <game3d/intersection.h>
#include <math/vector.h>
#include <googletest/googletest.h>

TEST(IntersectionResult,DefaultConstructor)
{
    IntersectResult ir;

    EXPECT_FALSE( ir.didHit() );
}
