#ifndef SCOTT_COMMON_STRING_UTIL_H
#define SCOTT_COMMON_STRING_UTIL_H

#include <string>
#include <ostream>
#include <sstream>
#include <stdint.h>

namespace StringUtil
{
    // Check if a string starts with another string
    bool startsWith( const std::string& word,
                     const std::string& prefix );

    // Check if a string ends with another string
    bool endsWith( const std::string& word,
                   const std::string& postfix );

    // Convert string to upper case
    std::string toUpper( const std::string& input );
    
    // Append a numeric value to a string
    std::string makeSuffix( const std::string& base, long suffix );

    // Take an input string and replace each occurrence of findStr with
    // replaceStr.
    std::string replace( const std::string& input,
                         const std::string& findStr,
                         const std::string& replaceStr );

    // Output byte array as hexadecimal
    std::ostream& printHex( std::ostream& stream,
                            const uint8_t *ptr,
                            size_t len );

    template<typename T>
    std::ostream& printHex( std::ostream& stream, const T& obj )
    {
        const uint8_t * pBase = reinterpret_cast<const uint8_t*>(&obj);
        return printHex( stream, pBase, sizeof(obj) );
    }

    // Output byte array as binary
    std::ostream& printBinary( std::ostream& stream,
                               const uint8_t *ptr,
                               size_t len );

    template<typename T>
    std::ostream& printBinary( std::ostream& stream, const T& obj )
    {
        const uint8_t *pBase = reinterpret_cast<const uint8_t*>(&obj);
        return printBinary( stream, pBase, sizeof(obj) );
    }
}

#endif
