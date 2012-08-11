#include <googletest/googletest.h>
#include <string/stringbuffer.h>
#include <string>

TEST(StringUtils,StringBuffer_Construct)
{
    std::string output;
    output = StringBuffer( output, 512 );
}
