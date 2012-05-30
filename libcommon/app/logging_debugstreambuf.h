/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SCOTT_COMMON_LOGGING_DEBUGSTREAMBUF_H
#define SCOTT_COMMON_LOGGING_DEBUGSTREAMBUF_H

#include "app/logging.h"
#include <ostream>
#include <streambuf>
#include <string>

#include <stdio.h>      // for EOF macro

/**
 * A custom debugging stream buffer implementation that is derived from the C++
 * IO Streams buffer. By doing this we can inject ourselves into the stream
 * interface, intercept all the data coming into the stream buffer and then be
 * able to output where ever we like.
 */
template<typename Char, typename Traits >
class DebugStreambuf : public std::basic_streambuf<Char, Traits>
{
public:
    typedef typename std::basic_streambuf<Char, Traits>::traits_type traits_type;
    typedef typename std::basic_streambuf<Char, Traits>::int_type int_type;

public:
    DebugStreambuf();
    DebugStreambuf( std::basic_streambuf<Char, Traits> *pConsoleBuffer,
                    std::basic_filebuf<Char,Traits> *pFileBuffer );
    virtual ~DebugStreambuf();

    void write( const std::basic_string<Char,Traits>& contents );
    void setConsoleThreshold( ELogLevel level );
    void setFileThreshold( ELogLevel level );

    void setConsole( std::basic_streambuf<Char, Traits> *pConsoleBuffer );
    void setFile( std::basic_filebuf<Char,Traits> *pFileBuffer );

    void startLogEntry( ELogLevel logLevel, const char* moduleName );
    void endLogEntry();

protected:
    virtual int overflow( int c = EOF );
    virtual int sync();
 //   std::streamsize write( const Char* pSequence, std::streamsize size );

    // Returns a textual version of the log level
    const char* getLogLevelString( ELogLevel level ) const;

    bool writeEntryHeaderConsole() const;
    bool writeEntryHeaderFile() const;

private:
    // Disable the copy constructor
    DebugStreambuf( const DebugStreambuf& );

    // Disable the assignment operator
    DebugStreambuf& operator = ( const DebugStreambuf& );

private:
    const std::size_t BUFFER_SIZE;
    char * mpInternalBuffer;

    std::basic_streambuf<Char,Traits> *mpConsoleBuffer;
    std::basic_filebuf<Char,Traits> *mpFileBuffer;

    // The default severity of a log entry
    const ELogLevel mDefaultLogLevel;

    // The default module name for a log entry
    const char * mDefaultModuleName;

    // The minimum threshold that must be met for log entry to written to
    // the user console
    ELogLevel mConsoleThreshold;

    // The minimum threshold that must be met for a log entry to be written
    // to the file log
    ELogLevel mFileThreshold;

    // Flag if we are writing the start of a new log entry
    bool mAtLineStart;

    // The severity level of the current log entry
    ELogLevel mLogLevel;

    // Module name for the current log entry
    const char * mModuleName;
};

#include "app/logging_debugstreambuf.inl"
#endif

