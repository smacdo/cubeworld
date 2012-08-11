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
#include <iostream>

namespace Assert
{
    /**
     * These are the default values used by the assertion system
     */
    namespace Constants
    {
        // Default message shown to users who experience an assertion failure
        const char * EXPLANATION =
            "The application has failed an internal assertion test, and must " \
            "exit. Please contact the developer to report this incident, and " \
            "include the following details.";

        // Default reason if none was passed (did not use ASSERT_MSG)
        const char * DEFAULT_REASON =
            "Expected expression to be true, was false instead";

        // Value to insert if function name or file name was not provided
        const char * UNKNOWN_PARAM = "Unknown";

        // Default assertion action (break into debugger)
        const EAssertAction DEFAULT_ACTION = EASSERT_BREAK;
    }

    /**
     * The currently installed assertion handler
     */
    assert_func_t GAssertHandler = defaultAssertHandler;

    /**
     * Raises an assertion. This will call the installed assertion handler, or
     * the default one if none was configured.
     *
     * Normally this will cause the assertion to print a message to the screen,
     * allow the user to handle it's resolution and the function will report
     * back what the user wishes to do.
     *
     * \param  pExpression  Text of the failing expression
     * \param  pReason      Message accompanying the assert (NULL for none)
     * \param  pFunction    Name of the function where the assert failed
     * \param  pFile        Name of the code file where the assert failed
     * \param  line         Line number of the file where the assert failed
     *
     * \return              True if the application should trigger a debug
     *                      break, false otherwise. (Will continue as if
     *                      nothing happened )
     */
    bool raiseAssertion( const char * pExpression,
                         const char * pReason,
                         const char * pFunction,
                         const char * pFile,
                         unsigned int line )
    {

        std::cerr << "FAILED ASSERTION FIRED" << std::endl;
        // Subsitute default values if they were not provided
        if ( pReason == NULL )
        {
            pReason = Constants::DEFAULT_REASON;
        }

        if ( pExpression == NULL )
        {
            pExpression = Constants::UNKNOWN_PARAM;
        }

        if ( pFunction == NULL )
        {
            pFunction = Constants::UNKNOWN_PARAM;
        }

        if ( pFile == NULL )
        {
            pFile = Constants::UNKNOWN_PARAM;
        }

        // Call the configured assertion handler if there is one. Otherwise
        // (in case of NULL) call the default assertion handler
        EAssertAction act = Constants::DEFAULT_ACTION;
        
        if ( GAssertHandler == NULL )
        {
            act = defaultAssertHandler( pExpression, pReason, pFunction, pFile, line );
        }
        else
        {
            act = GAssertHandler( pExpression, pReason, pFunction, pFile, line );
        }

        // Did the application request for us to exit right now?
        if ( act == EASSERT_EXIT )
        {
            exit( 4200 );
        }

        // Let the invoker know if they should be trigger a debug break right
        // now
        return ( act == EASSERT_BREAK );
    }

    /**
     * Sets a custom assertion handler
     */
    void setAssertHandler( assert_func_t pAssertHandler )
    {
        GAssertHandler = pAssertHandler;
    }

    /**
     * Returns the active assertion handler
     */
    assert_func_t getAssertHandler()
    {
        return GAssertHandler;
    }

    /**
     * The default assertion handler. It prints the details of a failed
     * assertion to the standard error stream, and then requests to terminate
     * the application
     */
    EAssertAction defaultAssertHandler( const char * pExpression,
                                        const char * pReason,
                                        const char * pFunction,
                                        const char * pFile,
                                        unsigned int line )
    {
        std::cerr
            << "******************** ASSERTION FAILED ********************\n"
            << Constants::EXPLANATION        << "\n"
            << "\n"
            << "REASON    : " << pReason     << "\n"
            << "EXPRESSION: " << pExpression << "\n"
            << "FUNCTION  : " << pFunction   << "\n"
            << "FILE      : " << pFile       << "\n"
            << "LINE      : " << line        << "\n"
            << "*********************************************************\n"
            << std::endl;

        return Constants::DEFAULT_ACTION;
    }
}
