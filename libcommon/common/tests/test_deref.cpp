/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <googletest/googletest.h>
#include <memory>

#include "common/deref.h"
#include "common/assert.h"


/**
 * Tests that we can deref a non-null pointer value
 */
TEST(UtilsTests,DerefValid)
{
    int v = 42;
    int *pV = &v;
    int& rV = deref( pV );

    EXPECT_EQ( 42, rV );

    rV = 250;
    EXPECT_EQ( 250, v );
    EXPECT_EQ( 250, *pV );
}

/**
 * Tests if we can deref a non-null constant pointer value
 */
TEST(UtilsTests,DerefConst)
{
    int v = 42;
    const int *pV = &v;

    EXPECT_EQ( 42, deref( pV ) );
}

/**
 * Tests if we can deref a non-null smart pointer value
 */
TEST(UtilsTest,DerefSmartPointer)
{
    std::shared_ptr<int> p( new int(42) );
    EXPECT_EQ( 42, deref( p ) );
}

/**
 * Tests if we can deref a non-null constant smart pointer value
 */
TEST(UtilsTest,DerefConstSmartPointer)
{
    std::shared_ptr<const int> p( new int(42) );
    EXPECT_EQ( 42, deref( p ) );
}

TEST(UtilsTests,DerefNullDeath)
{
    const int *pV = NULL;

    Debug::setTestAssertShouldDie( true );
    EXPECT_DEATH( deref( pV ), "ASSERTION FAILED: ptr != __null" );

    Debug::resetTestAssertShouldDie();
}

TEST(UtilsTests,DerefNullSmartPointerDeath)
{
    std::shared_ptr<int> p;

    Debug::setTestAssertShouldDie( true );
    EXPECT_DEATH( deref( p ), "ASSERTION FAILED: ptr != __null" );

    Debug::resetTestAssertShouldDie();
}
