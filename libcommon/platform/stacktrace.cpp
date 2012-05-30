#include <platform/stacktrace.h>
#include <execinfo.h>
#include <sstream>

#include <stdlib.h>

std::vector<std::string> GetStackTrace()
{
    const size_t               MaxReturns = 16;
    std::vector<std::string>   values;
    void                      *retAddresses[MaxReturns];
    char                     **retNames;
    std::stringstream          sstream;

    // Load list of return addresses
    size_t size = backtrace( retAddresses, MaxReturns );

    // Convert return addresses into names
    retNames = backtrace_symbols( retAddresses, size );

    // Copy into stack trace array
    for ( size_t i = 0; i < MaxReturns; ++i )
    {
        values[i] = std::string( retNames[i] );

        // Free allocate string
        free( retNames[i] );
    }

    // Free returned list of strings, and the return the array
    free( retNames );

    return values;
}
