#include <common/assert.h>
#include <googletest/googletest.h>
#include <iostream>

// Application assertion callback
namespace Debug
{
    bool GUnitTestMode                = false;
    bool GTestAssertShouldDie         = false;
    assertionHandler GAssertionHandler = NULL;

    void setAssertionHandler( assertionHandler handler )
    {
        GAssertionHandler = handler;
    }

    void setInUnitTestMode( bool isInUnitTestMode )
    {
        GUnitTestMode = isInUnitTestMode;       
    }

    void setTestAssertShouldDie( bool shouldDie )
    {
        GTestAssertShouldDie = shouldDie;
    }
    
    void resetTestAssertShouldDie()
    {
        setTestAssertShouldDie( true );
    }

    EAssertionStatus raiseAssertion( const char * pMessage,
                                     const char * pExpression,
                                     const char * pFile,
                                     unsigned int lineNumber )
    {
        // Validate our inputs. If any were not provided (NULL), then fill
        // them in with default values
        if ( pMessage == NULL )
        {
            pMessage = "The expression evaluated to false";
        }

        if ( pExpression == NULL )
        {
            pExpression = "(no expression provided)";
        }

        if ( pFile == NULL )
        {
            pFile = "unknown_file";
        }

        // We need to handle a special case of being in unit test mode. A
        // software assertion needs to perform special logic when running
        // into assertions while running unit tests
        if ( GUnitTestMode )
        {
            ADD_FAILURE_AT( pFile, static_cast<int>( lineNumber ) )
                << "Application assertion: "
                << pExpression;
            
            if ( GTestAssertShouldDie )
            {
                std::cerr
                    << "ASSERTION FAILED: "
                    << pExpression
                    << std::endl;

                exit( 1 );
            }
            
            return EAssertion_Continue;
        }

        // Do we have an assertion handler? Call it if we do, otherwise
        // fallback on a simple command line assertion
        EAssertionStatus status = EAssertion_Halt;

        if ( GAssertionHandler != NULL )
        {
            status = GAssertionHandler( pMessage,
                                        pExpression,
                                        pFile,
                                        lineNumber );
        }
        else
        {
            std::cerr
                << "********************************************" << std::endl
                << "Assertion failed!"                            << std::endl
                << ""                                             << std::endl
                << " MESSAGE   : " << pMessage                    << std::endl
                << " EXPRESSION: " << pExpression                 << std::endl
                << " SOURCE    : " << pFile << ":" << lineNumber  << std::endl
                << "********************************************" << std::endl
                ;
        }

        return status;
    }
}
