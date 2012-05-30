#include <googletest/googletest.h>
#include <string/util.h>

TEST(StringUtils,ReplaceStringOneOccurence)
{
    std::string input = "i have a dog";
    EXPECT_EQ( "i have a cat", replace( input, "dog", "cat" ) );
}

TEST(StringUtils,ReplaceStringMoreThanOnce)
{
    std::string input = "i have a dog and the dogs name is dog";
    EXPECT_EQ( "i have a cat and the cats name is cat",
               replace( input, "dog", "cat" ) );
}

TEST(StringUtils,ReplaceStringDoesNotReplaceReplacement)
{
    std::string input = "i have a dog and the dog is a dog";
    EXPECT_EQ( "i have a dogdog and the dogdog is a dogdog",
            replace( input, "dog", "dogdog" ) );
}

TEST(StringUtils,ReplaceStringReplacesInsideWords)
{
    std::string input = "today istoli unto though xto";
    EXPECT_EQ( "XXday isXXli unXX though xXX",
            replace( input, "to", "XX" ) );
}

TEST(StringUtils,ReplaceStringNoMatches)
{
    std::string input = "blah blah blah oh i see a cat";
    EXPECT_EQ( "blah blah blah oh i see a cat",
            replace( input, "dog", "cat" ) );
}
