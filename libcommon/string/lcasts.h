#ifndef SCOTT_COMMON_STRING_CASTS
#define SCOTT_COMMON_STRING_CASTS

#include <string>
#include <sstream>

namespace String
{
    /**
     * Attempts to lexically convert the given object into a STL
     * string. This asssumes that the objec's type supports stream
     * out operation.
     *
     * Great for converting base types (such as ints, floats) into
     * strings
     */
    template<typename T>
    inline std::string ToString( const T& object )
    {
        std::stringstream ss;
        ss << object;

        if ( ss.bad() ) // is this correct?
        {
            raiseError("Cast Failed")
                << "Failed to cast type to string: '"
                << object
                << "'";

            return "<cast failed>";
        }
        else
        {
            return ss.str();
        }
    }

    /**
     * Attempt to lexically convert a string value into the requested
     * type. An object must implement the stream in ( >> ) operator for
     * this method to work.
     *
     * All builtins function fine with this method without any extra
     * code.
     *
     * \return Returns true if the conversion succeeded, false otherwise
     */
    template<typename T>
    inline bool FromStringCast( const std::string& input, const T& output )
    {
        std::stringstream ss;
        ss << input;
        ss >> output;

        if ( ss.bad() )
        {
            raiseError("Cast Failed")
                << "Failed to cast from string to type: '"
                << input
                << "'";

            return false;
        }
        else
        {
            return true;
        }
    }

    template<typename ToT, typename FromT>
    inline ToT LexicalCast( const FromT& input )
    {
        ToT out;
        std::stringstream ss;

        ss << input;
        ss >> out;

        return out;
    }
}

#endif
