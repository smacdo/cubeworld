#ifndef SCOTT_COMMON_UNITTESTS_H
#define SCOTT_COMMON_UNITTESTS_H

#include <common/assert.h>

namespace UTest
{
    void assertDeath( bool shouldDie );
    void resetAssertDeath();

    Assert::EAssertAction testAssertHandler( const char *,
                                             const char *,
                                             const char *,
                                             const char *,
                                             unsigned int );
}

#endif
