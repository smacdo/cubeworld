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
#include <common/assert.h>
#include <googletest/googletest.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace UTest {

bool GExitOnAssert = false;

/**
 * Informs the unit test framework that any upcoming assertion is "expected"
 * and should therefore cause the process to exit. This allows us to utilize
 * Google's death test features when testing for expected assertions.
 *
 * Remember to reset this once the expected assertion has triggered, otherwise
 * any failing assertion will terminate the unit testing process
 */
void assertDeath( bool shouldDie )
{
    GExitOnAssert = shouldDie;
}

/**
 * Reset the death assertion handling to it's default state. (Report, but
 * continue)
 */
void resetAssertDeath()
{
    assertDeath( false );
}

/**
 * Generates a assertion reporting dialog (or console output) to show to the
 * player, before exiting the application
 *
 * \param  message     An accompanying assertion description (if provided)
 * \param  expression  String containing the expression text
 * \param  filename    Name of the file that generated the assertion
 * \param  lineNumber  Line that generated the assertion
 */
Assert::EAssertAction testAssertHandler( const char * pExpression,
                                         const char * /*pReason*/,
                                         const char * /*pFunction*/,
                                         const char * pFile,
                                         unsigned int line )
{
    std::cerr << "ASSERTION FAILED: " << pExpression << std::endl;

    ADD_FAILURE_AT( pFile, static_cast<int>( line ) )
        << "Application assertion: "
        << pExpression;

    if ( GExitOnAssert )
    {
        return Assert::EASSERT_EXIT;
    }
    else
    {
        return Assert::EASSERT_CONTINUE;
    }
}

}
