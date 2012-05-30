#include <string/util.h>
#include <string>

std::string replace( const std::string& input,
                     const std::string& findStr,
                     const std::string& replaceStr )
{
    std::string output( input );
    
    std::string::size_type pos   = input.find( findStr );
    std::string::size_type fSize = findStr.size(),
                           rSize = replaceStr.size();

    while ( pos != std::string::npos )
    {
        output.replace( pos, fSize, replaceStr );

        pos += rSize;
        pos  = output.find( findStr, pos );
    }

    return output;
}
