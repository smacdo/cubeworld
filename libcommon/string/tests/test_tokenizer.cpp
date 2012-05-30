/**
 * String tokenizer unit tests
 */
#include <string/tokenizer.h>
#include <googletest/googletest.h>

TEST(StringTokenizer,CreateItAndDoNothingOfUseWhatsoever)
{
    StringTokenizer st( "hallo" );
    EXPECT_FALSE( st.hasError() );
}

TEST(StringTokenizer,TokenizeASingleWord)
{
    // init
    StringTokenizer st( "hallo" );
    EXPECT_FALSE( st.hasError() );
    EXPECT_TRUE( st.hasNext()   );

    // first and only token
    std::string token = st.nextToken();
    EXPECT_EQ( "hallo", token );
    EXPECT_FALSE( st.hasError() );
    EXPECT_FALSE( st.hasNext()  );
}

TEST(StringTokenizer,TokenizerTokenizesTwoWords)
{
    StringTokenizer st( "hello world" );
    std::string token;

    // first token
    token = st.nextToken();
    EXPECT_EQ( "hello", token );
    EXPECT_TRUE( st.hasNext() );
    EXPECT_FALSE( st.hasError() );

    // second token
    token = st.nextToken();
    EXPECT_EQ( "world", token );
    EXPECT_FALSE( st.hasNext() );
    EXPECT_FALSE( st.hasError() );
}

TEST(StringTokenizer,TokenizerWithSymbol)
{
    StringTokenizer st( "1 + 2");

    EXPECT_EQ( "1", st.nextToken() );
    EXPECT_EQ( "+", st.nextToken() );
    EXPECT_EQ( "2", st.nextToken() );

    EXPECT_FALSE( st.hasError() );
    EXPECT_FALSE( st.hasNext()  );
}

TEST(StringTokenizer,TokenizerWithTwoConsequtiveSymbols)
{
    StringTokenizer st("1 += 2");

    EXPECT_EQ( "1", st.nextToken() );
    EXPECT_EQ( "+", st.nextToken() );
    EXPECT_EQ( "=", st.nextToken() );
    EXPECT_EQ( "2", st.nextToken() );
}

TEST(StringTokenizer,TokenizerWithTwoSymbolsInterleaved)
{
    StringTokenizer st("mary = beth . jane");

    EXPECT_EQ( "mary", st.nextToken() );
    EXPECT_EQ( "=",    st.nextToken() );
    EXPECT_EQ( "beth", st.nextToken() );
    EXPECT_EQ( ".",    st.nextToken() );
    EXPECT_EQ( "jane", st.nextToken() );
}

TEST(StringTokenizer,TokenizesBasicExpression)
{
    StringTokenizer st( "apples = tree.apples:count * 22" );

    EXPECT_EQ( "apples", st.nextToken() );
    EXPECT_EQ( "=",      st.nextToken() );
    EXPECT_EQ( "tree",   st.nextToken() );
    EXPECT_EQ( ".",      st.nextToken() );
    EXPECT_EQ( "apples", st.nextToken() );
    EXPECT_EQ( ":",      st.nextToken() );
    EXPECT_EQ( "count",  st.nextToken() );
    EXPECT_EQ( "*",      st.nextToken() );
    EXPECT_EQ( "22",     st.nextToken() );

    EXPECT_FALSE( st.hasError() );
    EXPECT_FALSE( st.hasNext()  );
}

TEST(StringTokenizer,TokenizerWithEmptyString)
{
    StringTokenizer st( "    hello world    ");

    // first token
    EXPECT_EQ( "hello", st.nextToken() );

    // second token
    EXPECT_EQ( "world", st.nextToken() );

    // all done?
    EXPECT_FALSE( st.hasError() );
    EXPECT_FALSE( st.hasNext()  );
}

TEST(StringTokenizer,TokenizerGoPastLastTokenTriggersError)
{
    StringTokenizer st( "hello world" );

    EXPECT_EQ( "hello", st.nextToken() );
    EXPECT_EQ( "world", st.nextToken() );
    EXPECT_FALSE( st.hasError() );

    EXPECT_EQ( "",      st.nextToken() );
    EXPECT_TRUE( st.hasError() );
    EXPECT_FALSE( st.hasNext() );
    EXPECT_EQ( std::string(), st.currentToken() );
}

