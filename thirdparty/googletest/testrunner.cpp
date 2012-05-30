#include "googletest/googletest.h"
#include "common/assert.h"

int main( int argc, char * argv[] )
{
//    Debug::setInUnitTestMode( true );

    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
