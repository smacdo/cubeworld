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
 * \param  pExpression  Text of the failing expression
 * \param  pReason      Message accompanying the assert (NULL for none)
 * \param  pFunction    Name of the function where the assert failed
 * \param  pFile        Name of the code file where the assert failed
 * \param  line         Line number of the file where the assert failed
 */
Assert::EAssertAction reportAssertion( const char * expression,
                                       const char * reason,
                                       const char * function,
                                       const char * file,
                                       unsigned int lineNumber )
{
    // Convert the assertion message into an NSString and use it as the
    // main dialog message
    NSString *pMessage = [[NSString alloc] initWithUTF8String: reason];

    // Format the assertion message to be better viewed in a dialog box
    NSString *pAssertion =
        [NSString stringWithFormat: @"assert( %s )\n%s:%u",
                                    expression,
                                    filename,
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
        return Assert::EASSERT_EXIT;
    }
    else
    {
        return Assert::EASSERT_BREAK;
    }
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
    Assert::setAssertHandler( reportAssertion );
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
