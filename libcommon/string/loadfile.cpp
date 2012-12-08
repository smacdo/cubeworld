#include <string/util.h>
#include <common/delete.h>

#include <boost/scoped_array.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace StringUtils {

/**
 * Loads a text file from disk and returns it's contents as a STL string.
 * This method can optionally indicate the success or failure of the
 * attempted operation.
 *
 * \param  filename   Path to the file
 * \param  pStatus    Optional boolean pointer, indicates success/fail
 * \return            Contents of the file
 */
std::string loadfile( const std::string& filename, bool * pStatus )
{
    using namespace std;
    string contents;
    bool status = true;

    ifstream ifs( filename.c_str(), ios::in | ios::binary | ios::ate );

    // Check if we were able to succesfully open the file before
    // proceeding.
    if ( ifs.good() )
    {
        // Find out the size of the file
        ifstream::pos_type fileSize = ifs.tellg();
        ifs.seekg( 0, ios::beg );

        // Slurp the file into a temporary byte array
        vector<char> bytes( static_cast<size_t>(fileSize) );
        ifs.read( &bytes[0], fileSize );

        // Convert the byte array into a temporary string and then swap
        // the return string
        std::string temp( &bytes[0], static_cast<size_t>(fileSize) );

        contents.swap( temp );
    }

    // Let the caller know the results of the file load
    if ( pStatus != NULL )
    {
        *pStatus = ifs.good();
    }

    return contents;
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
