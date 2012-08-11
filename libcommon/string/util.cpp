#include <string/util.h>
#include <common/assert.h>
#include <string>
#include <cstring>

namespace Util
{

/**
 * Checks if a word starts with the given prefix. Returns true if "word"
 * starts with "prefix".
 *
 * \param  word    The word to check
 * \param  prefix  The prefix to check
 */
std::string startsWith( const std::string& word,
                        const std::string& prefix )
{
    CORE_ASSERT( word.size() <= prefix.size(), "Prefix must be shorter than the word" );
    bool check = false;

    for ( size_t i = 0; i < prefix.size() && (!check); ++i )
    {
        check = ( word[i] == prefix[i] );
    }
}

std::string endsWith( const std::string& word,
                      const std::string& suffix )
{

}

}
