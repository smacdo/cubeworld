#include <string/util.h>
#include <app/debug.h>
#include <string>

#include <stdint.h>

std::ostream& printHex( std::ostream& stream,
                        const uint8_t *ptr,
                        size_t len )
{
    const char * CHARS = "0123456789ABCDEF";

    // bail out of the pointer is null
    if ( ptr == NULL )
    {
        stream << "(null)" << std::endl;
        return stream;
    }

    // print the hex header
    stream << "0x";

    // now print each hex character (two char per byte)
    for ( size_t i = 0; i < len; ++i )
    {
        stream << CHARS[ ptr[i] >> 4    ]
               << CHARS[ ptr[i]  & 0x0F ];
    }

    return stream;
}

std::ostream& printBinary( std::ostream& stream,
                           const uint8_t *ptr,
                           size_t len )
{
    // Bail out if the pointer is null
    if ( ptr == NULL )
    {
        stream << "(null";
        return stream;
    }

    // print the binary header
    stream << "0b";

    // print each bit of the data stream, allowing for a space every
    // 8 digits
    for ( size_t i = 0; i < len; ++i )
    {
        uint8_t v = ptr[i];

        stream <<  (v >> 7)
               << ((v >> 6) & 0x1)
               << ((v >> 5) & 0x1)
               << ((v >> 4) & 0x1)
               << ((v >> 3) & 0x1)
               << ((v >> 2) & 0x1)
               << ((v >> 1) & 0x1)
               << ((v     ) & 0x1);

        if ( i != len )
        {
            stream << " ";
        }
    }

    return stream;
}
