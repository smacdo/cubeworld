#include <googletest/googletest.h>
#include <string/util.h>
#include <sstream>

using namespace StringUtil;

TEST(StringUtils,ZeroByteToHex)
{
    uint8_t v = 0;
    std::ostringstream ss;

    printHex( ss, v );

    EXPECT_EQ( "0x00", ss.str() );
}

TEST(StringUtils,SimpleByteToHex)
{
    uint8_t v = 42;
    std::ostringstream ss;

    printHex( ss, v );

    EXPECT_EQ( "0x2A", ss.str() );
}

TEST(StringUtils,IntToHex)
{
    int32_t v = 20481024;
    std::ostringstream ss;

    printHex( ss, v );

    //EXPECT_EQ( "0x01388400", ss.str() );        // MSB
    EXPECT_EQ( "0x00843801", ss.str() );
}

TEST(StringUtils,ZeroByteToBinary)
{
    uint8_t v = 0;
    std::ostringstream ss;

    printBinary( ss, v );
    EXPECT_EQ( "0b00000000 ", ss.str() );
}

TEST(StringUtils,SimpleByteToBinary)
{
    uint8_t v = 42;
    std::ostringstream ss;

    printBinary( ss, v );
    EXPECT_EQ( "0b00101010 ", ss.str() );
}

TEST(StringUtils,DoubleByteToBinary)
{
    uint16_t v = 1001;
    std::ostringstream ss;

    printBinary( ss, v );
    EXPECT_EQ( "0b11101001 00000011 ", ss.str() );
}
