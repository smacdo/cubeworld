#include <string/util.h>
#include <common/delete.h>

#include <boost/scoped_array.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace StringUtils {

/**
 * Loads a text file from disk, and returns the output
 *
 * \param  filename   Path to the file
 * \param  pStatus    Optional boolean pointer, indicates success/fail
 * \return            Contents of the file
 */
std::string loadfile( const std::string& filename, bool * pStatus )
{
    std::string output;
    output.reserve( 4096 );

    // Open requested file and make sure we were able to load it
    std::ifstream file( filename.c_str(), std::ios::ate );

    if ( file.good() )
    {
        // Get the size of the file, so we know how large of a buffer to
        // allocate. Then read the contents of that file into this buffer
        size_t size = static_cast<size_t>( file.tellg() );
        boost::scoped_array<char> pBuffer( new char[ size ] );

        file.read( pBuffer.get(), size );

        // Copy the file buffer into an STL string for returning
        output.append( pBuffer.get(), size );

        // Let the caller know that we succeeded in loading the file
        if ( pStatus != NULL )
        {
            *pStatus = ( file.fail() == false );
        }
    }
    else
    {
        // Let the caller know that we were not successful in loading the
        // file
        if ( pStatus != NULL )
        {
            *pStatus = false;
        }
    }

    return output;
}

/**
 * Loads a text file into an array of strings. Each entry corresponds to
 * a line of text from the file
 */
std::vector<std::string> loadFileIntoArray( const std::string& filename,
                                            bool *pStatus )
{
    std::vector<std::string> output;

    // Open the file, and read all the lines from it
    std::ifstream file( filename.c_str(), std::ios::ate );

    if ( file.good() )
    {
        std::string line;

        while ( std::getline( file, line ) )
        {
            output.push_back( line );
        }

        // if caller provided a status pointer, indicate if the file read
        // was successful
        if ( pStatus != NULL )
        {
            *pStatus = ( file.fail() == false );
        }
    }
    else
    {
        // File failed to load
        if ( pStatus != NULL )
        {
            *pStatus = false;
        }
    }

    return output;
}

}
