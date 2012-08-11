/**
 * Copyright 2010 Scott MacDonald. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY SCOTT MACDONALD ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Scott MacDonald.
 */
#ifndef SCOTT_COMMON_STRING_TOKENIZER_H
#define SCOTT_COMMON_STRING_TOKENIZER_H

#include <string>

/**
 * A very simple string tokenizer that transforms a string into a set
 * of tokens using built-in rules. Tokens are seperated from each other
 * by either whitespace or an operator character.
 *
 * \w*([A-Za-z0-9_]+)(\w|CONTROL_CHARS)
 */
class StringTokenizer
{
public:
    /**
     * Initialize the string tokenizer with an input string
     */
    StringTokenizer( const std::string& input );

    /**
     * Indicates if the tokenizer has more tokens to consume. This will
     * return false if the tokenizer is in an error state.
     */
    bool hasNext() const;

    /**
     * Indicates if the tokenizer is in an error state.
     */
    bool hasError() const;

    /**
     * Returns the first character position that caused the last error.
     * Not valid if the parser is not in an error state.
     */
    size_t errorPos() const;

    /**
     * Returns a human readable string that describes the error
     * Note valid if the parser is not in an error state.
     */
    std::string errorString() const;

    /**
     * Returns the next parsed token from the input string. If you
     * continue to request tokens from the tokenizer when there are none
     * left, the tokenizer will go into an error state and this method
     * will return empty strings.
     */
    std::string nextToken();

    /**
     * Returns the current parsed token from the input string
     */
    std::string currentToken() const;

private:
    /**
     * Internal method that contains the parsing logic. It will start
     * from the last point it left off, and create a new token. This will
     * set an error state if there are problems with parsing, or if the
     * user attempts to go beyond the end of the string.
     */
    void parseNext();

    /**
     * Internal helper method that allows the tokenizer to raise an
     * error condition. Once raised, the parser will no longer function
     * and it will report the error
     */
    void raiseError( size_t pos, const std::string& message );

    /**
     * Helper method used by the constructor. It will remove excess spaces
     * from both the beginning and the end of the input string.
     */
    std::string trimString( const std::string& input ) const;

private:
    size_t m_startpos;
    size_t m_endpos;
    size_t m_errorpos;
    std::string m_input;
    std::string m_lastToken;
    std::string m_currentToken;
    std::string m_errorStr;
    bool m_hasNextToken;
    bool m_errorFlag;
};

#endif

