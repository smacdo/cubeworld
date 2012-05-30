/**
 * Unit tests for ray class
 */
#include <game3d/ray.h>
#include <math/vector.h>
#include <googletest/googletest.h>

TEST(Geoms,SimpleRay)
{
    Ray r( Vec3(1,1,1), Vec3(1,0,0) );

    EXPECT_EQ( Vec3(1,1,1), r.origin()    );
    EXPECT_EQ( Vec3(1,0,0), r.direction() );
}
