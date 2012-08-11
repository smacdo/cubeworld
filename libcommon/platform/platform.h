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
#ifndef SCOTT_COMMON_APP_PLATFORM_H
#define SCOTT_COMMON_APP_PLATFORM_H

// Common includes
#include "common/macros.h"
#include "common/assert.h"
#include "common/time.h"
#include "app/debug.h"

// System includes
#include <string>

/////////////////////////////////////////////////////////////////////////////
// Internal application utility functions
/////////////////////////////////////////////////////////////////////////////
namespace App
{
    enum EProgramStatus
    {
        EPROGRAM_OK = 0,
        EPROGRAM_ASSERT_FAILED = 2,
        EPROGRAM_FATAL_ERROR   = 5,
        EPROGRAM_USER_ERROR    = 6
    };

    enum EErrorType
    {
        EERROR_WARNING,
        EERROR_ERROR,
        EERROR_FATAL
    };

    // Converts an error type enum into a string
    std::string getNameForError( EErrorType error );

    // Performs any needed platform specific work before starting the game
    void startup();

    // Quit the application
    void quit( EProgramStatus quitStatus, const std::string& message = "" );

    // Get the current system time
    Time currentTime();

    // Wait a certain amount of time
    void sleep( Time time );

    // Raise an error
    void raiseError( const std::string& message,
                     const std::string& details = "" );

    // Raise a fatal error
    void raiseFatalError( const std::string& message,
                          const std::string& details = "" );

    // Report a code assertion
    Assert::EAssertAction reportAssertion( const char *pExpression,
                                           const char *pReason,
                                           const char *pFunction,
                                           const char *pFile,
                                           unsigned int line );

    // Platform specific error reporting
    void reportSoftwareError( const std::string& message,
                              const std::string& details,
                              EErrorType type,
                              unsigned int lineNumber,
                              const char * fileName,
                              const char * functionName );

    // Returns a "build string", which is a long string containing information
    // about the settings under which the game was built
    std::string getBuildString();
}

#endif
