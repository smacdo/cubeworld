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
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

namespace App {

/**
 * Generates a assertion reporting dialog (or console output) to show to the
 * player, before exiting the application
 *
 * \param  message     An accompanying assertion description (if provided)
 * \param  expression  String containing the expression text
 * \param  filename    Name of the file that generated the assertion
 * \param  lineNumber  Line that generated the assertion
 */
Debug::EAssertionStatus reportAssertion( const std::string& message,
                                         const std::string& expression,
                                         const std::string& filename,
                                         unsigned int lineNumber )
{
    // Convert the assertion message into an NSString and use it as the
    // main dialog message
    NSString *pMessage = [[NSString alloc] initWithUTF8String: message.c_str()];

    // Format the assertion message to be better viewed in a dialog box
    NSString *pAssertion =
        [NSString stringWithFormat: @"assert( %s )\n%s:%u",
                                    expression.c_str(),
                                    filename.c_str(),
                                    lineNumber ];

    NSAlert *pAlert = [[NSAlert alloc] init];
    [ pAlert setMessageText: pMessage ];
    [ pAlert setInformativeText: pAssertion ];
    [ pAlert addButtonWithTitle: @"Debug crash" ];
    [ pAlert addButtonWithTitle: @"Quit application" ];

    // Display the dialog to the user, and wait for a response. Should we start
    // the debugger, or do we simply exit the game?
    NSInteger status = [ pAlert runModal ];

    if ( status == 1 )
    {
        // User wants to exit, so just crash
        App::quit( App::EPROGRAM_ASSERT_FAILED );
    }

    // Now return and let the caller know that they should abort
    return Debug::EAssertion_Halt;
}

/**
 * Platform specific error reporting utility. This method is called by the
 * game engine whenever there is an error (or warning) to be reported. The
 * method is responsible for providing this information to the user and 
 * allowing the player to take appropriate action based on it.
 *
 * \param  message       A terse description of the error that occurred
 * \param  details       Optional contextual details of the error
 * \param  type          What type of error is this
 * \param  lineNumber    Line number that this error occurred on
 * \param  functionName  Name of the function where error occurred
 */
void reportSoftwareError( const std::string& message,
                          const std::string& details,
                          EErrorType type,
                          unsigned int lineNumber,
                          const char * filename,
                          const char * functionName )
{
    // Convert STL strings into apple's NSString
    NSString *pMessage = [[NSString alloc] initWithUTF8String: message.c_str()];

    // Generate an informative message detailing what exatly went wrong
    NSString *pDetails = 
        [NSString stringWithFormat: @"%s\n%s (%s:%u)",
                                    details.c_str(),
                                    functionName,
                                    filename,
                                    lineNumber ];

    // Create the software alert dialog box, and configure it
    NSAlert *pAlert = [ [NSAlert alloc] init ];
    [ pAlert setMessageText: pMessage ];
    [ pAlert setInformativeText: pDetails ];

    // What kind of error is this? Configure alert dialog to match
    switch ( type )
    {
        case EERROR_WARNING:
            [ pAlert setAlertStyle: NSWarningAlertStyle ];
            break;

        case EERROR_ERROR:
            [ pAlert setAlertStyle: NSCriticalAlertStyle ];
            break;

        case EERROR_FATAL:
            [ pAlert setAlertStyle: NSCriticalAlertStyle ];
            break;

    }

    [ pAlert runModal ];
}

/**
 * Performs UNIX specific start up tasks
 */
void startup()
{
}

/**
 * Quit the program with the requested status and reason
 */
void quit( EProgramStatus programStatus, const std::string& message )
{
    if (! message.empty() )
    {
        std::cerr << "EXITING: " << message << std::endl;
    }

    exit( programStatus );
}


}
