#ifndef SCOTT_COMMON_STRING_STRINGBUFFER_H
#define SCOTT_COMMON_STRING_STRINGBUFFER_H

#include <string>
#include <vector>
#include <iterator>

/**
 * Utilty class that assists when calling legacy functions
 * (Especially with windows api). It allows you to declare a normal
 * STL string, and then use this class to automate passing a fixed size
 * buffer into a method and upon completion copies it to your STL string.
 *
 * An example is worth a thousand words, so here it is:
 * *****
 * std::string str;
 * GetApplicationName( TransferString(str, MAX_SIZE), MAX_SIZE );
 * *****
 *
 * TransferString passes a writeable cstring buffer to the function, and
 * then upon destruction it copies the value into str.
 *
 * Inspiration from:
 * http://stackoverflow.com/questions/469696/what-is-your-most-useful-c-c-utility/473786#473786
 * 
 */
template<class T>
class TransferStringImpl
{
    typename std::basic_string<T>& mStringOut;
    typename std::vector<T>        mInputBuffer;

public:
    /**
     * Create a new string buffer
     *
     * \param  str   STL string to copy output to when finished
     * \param  size  Maximum buffer size to allocate
     */
    TransferStringImpl( std::basic_string<T>& str, size_t size )
        : mStringOut( str ),
          mInputBuffer( size + 1 )
    {
        // Set last element of buffer to be zero (null terminated)
        bufferPtr()[size] = static_cast<T>( 0 );
    }

    /**
     * Destructor. Calls commit which will copy the inputted c-string into
     * the output STL string
     */
    ~TransferStringImpl()
    {
        commit();
    }

    /**
     * Get a pointer to the internal c-string buffer
     *
     * \return  Pointer to the internal c-string buffer
     */
    T *bufferPtr()
    {
        return &mInputBuffer[0];
    }

    /**
     * Implicit conversion operator. Allows this instance to be implicitly
     * converted in a c-string.
     */
    operator T *()
    {
        return bufferPtr();
    }

    /**
     * Commits the temporary c-string buffer into a user specified STL string
     * for preservation. This is where the magic happens - When this method
     * is called, the input buffer (a c-string) is copied into a STL string
     * that the user specified. Ownership of the string contents is
     * transferred, and the original c-string buffer is destroyed.
     */
    void commit()
    {
        // Refuse to do anything if buffer size is zero
        if ( mInputBuffer.size() == 0 )
        {
            return;
        }

        // Get the length of the cstring, and copy it to provided STL string
        size_t len = std::char_traits<T>::length( bufferPtr() );
        mStringOut.assign( bufferPtr(), len );

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
        mInputBuffer.resize( 0 );
    }
};

template<typename T>
inline TransferStringImpl<T> TransferString( typename std::basic_string<T>& str,
                                             size_t size )
{
    return TransferStringImpl<T>( str, size );
}

#endif
