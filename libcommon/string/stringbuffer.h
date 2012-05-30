#ifndef SCOTT_COMMON_STRING_STRINGBUFFER_H
#define SCOTT_COMMON_STRING_STRINGBUFFER_H

#include <string>
#include <vector>
#include <traits>

/**
 * Utilty class that assists when calling legacy functions
 * (Especially with windows api). It allows you to declare a normal
 * STL string, and then use this class to automate passing a fixed size
 * buffer into a method and upon completion copies it to your STL string.
 *
 * An example is worth a thousand words, so here it is:
 * *****
 * std::string str;
 * GetApplicationName( StringBuffer(str, MAX_SIZE), MAX_SIZE );
 * *****
 *
 * StringBuffer passes a writeable cstring buffer to the function, and
 * then upon destruction it copies the value into str.
 *
 * Inspiration from:
 * http://stackoverflow.com/questions/469696/what-is-your-most-useful-c-c-utility/473786#473786
 * 
 */
template<class T>
class StringBufferImpl
{
    typename std::basic_string<T>& m_str;
    typename std::vector<T>        m_buffer;

public:
    StringBufferImpl( std::basic_string<T>& str, size_t size )
        : m_str( str ),
          m_buffer( size + 1 )
    {
        // Set last element of buffer to be zero (null terminated)
        bufferPtr()[size] = static_cast<T>( 0 );
    }

    ~StringBufferImpl()
    {
        commit();
    }

    T *bufferPtr()
    {
        return &m_buffer[0];
    }

    operator T *()
    {
        return bufferPtr();
    }

    void commit()
    {
        // Refuse to do anything if buffer size is zero
        if ( m_buffer.size() == 0 )
        {
            return;
        }

        // Get the length of the cstring, and copy it to provided STL string
        size_t len = std::char_traits<T>::length( bufferPtr() );
        m_str.assign( bufferPtr(), len );

        // Not sure why the author is trying to resize the buffer to be
        // zero. Will keep this here until I can understand what he was
        // trying to accomplish (if anything)
        abort();
    }

    // Not at all sure why the author had an abort method included. I'll
    // include it verbatim just in case there's justification for it
    // down the road
    void abort()
    {
        m_buffer.resize( 0 );
    }
};

template<typename T>
inline StringBuffer<T> StringBuffer( typename std::basic_string<T>& str,
                                     size_t size )
{
    return StringBufferImpl<T>( str, size );
}

#endif
