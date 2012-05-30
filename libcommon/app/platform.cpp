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
#include "app/platform.h"
#include <googletest/googletest.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace App {

/**
 * Returns a human readable string for the given error enum type
 */
std::string getNameForError( EErrorType type )
{
    switch ( type )
    {
        case EERROR_WARNING:
            return "warning";
        case EERROR_ERROR:
            return "error";
        case EERROR_FATAL:
            return "fatal";
    }

    return "unknown error type";
}

/**
 * Generates a non-fatal error message that is displayed to the player, and
 * the player is allowed to choose whether to continue or quit.
 *
 * \param  message  The main error message
 * \param  details  (optional) Details about the problem
 */
void raiseError( const std::string& message,
                 const std::string& details )
{
    reportSoftwareError( message, details, EERROR_ERROR, 0, NULL, NULL );
}

/**
 * Displays a fatal error message to the player before he/she is forced to
 * quit playing.
 *
 * \param  message  The main error message
 * \param  details  (optional) Details about the problem
 */
void raiseFatalError( const std::string& message,
                      const std::string& details )
{
    reportSoftwareError( message, details, EERROR_FATAL, 0, NULL, NULL );
    App::quit( EPROGRAM_FATAL_ERROR, message );
}

/**
 * Returns a string describing the conditions under which the game was
 * built. Useful for troubleshooting, and that's about it
 */
std::string getBuildString()
{
    std::ostringstream ss;

    // All the settings we'll need to discover
    std::string releaseMode = "_?release?_";
    std::string processor   = "_?cpu?_";
    std::string platform    = "_?platform?_";
    std::string sse         = "_?sse?_";
    std::string compiler    = "_?compiler?_";

    // need to implement this

    // Properly format the build string according to the compiler
    ss << "VERSION_MISSING" << " "
       << sse         << " "
       << platform    << " "
       << __DATE__    << " "
       << __TIME__    << " "
        ;

    // Return the build string
    return ss.str();
}

}
