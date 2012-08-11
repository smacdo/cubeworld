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
#include <testing/testing.h>
#include <memory>

#include "common/deref.h"
#include "common/assert.h"


/**
 * Tests that we can deref a non-null pointer value
 */
TEST(DerefTests,Pointer)
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
 * Test if we can deref a non-null constant pointer value
 */
TEST(DerefTests,ConstPointer)
{
    int v = 42;
    const int *pV = &v;

    EXPECT_EQ( 42, deref( pV ) );
}

/**
 * Test if we can deref a non-null smart pointer value
 */
TEST(DerefTest,SmartPointer)
{
    std::shared_ptr<int> p( new int(42) );
    EXPECT_EQ( 42, deref( p ) );
}

/**
 * Tests if we can deref a non-null constant smart pointer value
 */
TEST(DerefTest,ConstSmartPointer)
{
    std::shared_ptr<const int> p( new int(42) );
    EXPECT_EQ( 42, deref( p ) );
}

/**
 * Test if dereferencing a null pointer causes death
 */
TEST(DerefDeathTests,NullPointer)
{
    int *pV = NULL;

    UTest::assertDeath( true );
    EXPECT_DEATH( deref( pV ), "ASSERTION FAILED: ptr != NULL" );

    UTest::resetAssertDeath();
}

/**
 * Test if dereferencing a null constant pointer causes death
 */
TEST(DerefDeathTests,NullConstPointer)
{
    const int *pV = NULL;

    UTest::assertDeath( true );
    EXPECT_DEATH( deref( pV ), "ASSERTION FAILED: ptr != NULL" );

    UTest::resetAssertDeath();
}

/**
 * Test if dereferncing a null smart pointer causes death
 */
TEST(DerefDeathTests,NullSmartPointer)
{
    std::shared_ptr<int> p;

    UTest::assertDeath( true );
    EXPECT_DEATH( deref( p ), "ASSERTION FAILED: ptr != NULL" );

    UTest::resetAssertDeath();
}
