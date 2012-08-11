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
#ifndef SCOTT_COMMON_LOGGING_DEBUGSTREAMBUF_INL_H
#define SCOTT_COMMON_LOGGING_DEBUGSTREAMBUF_INL_H
#include "app/logging.h"
#include "app/logging_debugstreambuf.h"
#include "app/debug.h"
#include "common/delete.h"
#include "common/assert.h"
#include <sstream>
#include <ctime>

#include <ostream>
#include <fstream>
#include <streambuf>

/**
 * The debug stream buffer constructor. Takes a pointer to a stream buffer
 * that acts as a backing store.
 */
template<typename C, typename T>
DebugStreambuf<C,T>::DebugStreambuf()
    : BUFFER_SIZE( 4096 ),
      mpInternalBuffer( new char[BUFFER_SIZE] ),
      mpConsoleBuffer( NULL ),
      mpFileBuffer( NULL ),
      mDefaultLogLevel( ELOGLEVEL_INFO ),
      mDefaultModuleName( "App" ),
      mConsoleThreshold( ELOGLEVEL_DEBUG ),
      mFileThreshold( ELOGLEVEL_DEBUG ),
      mAtLineStart( true ),
      mLogLevel( mDefaultLogLevel ),
      mModuleName( mDefaultModuleName )
{
    std::basic_streambuf<C,T>::setp( &mpInternalBuffer[0], &mpInternalBuffer[BUFFER_SIZE] );
}

/**
 * The debug stream buffer constructor. Takes a pointer to a stream buffer
 * that acts as a backing store.
 */
template<typename C, typename T>
DebugStreambuf<C,T>::DebugStreambuf( std::basic_streambuf<C,T>* pConsoleBuffer,
                                     std::basic_filebuf<C,T>* pFileBuffer )
    : BUFFER_SIZE( 4096 ),
      mpInternalBuffer( new char[BUFFER_SIZE] ),
      mpConsoleBuffer( pConsoleBuffer ),
      mpFileBuffer( pFileBuffer ),
      mDefaultLogLevel( ELOGLEVEL_INFO ),
      mDefaultModuleName( "App" ),
      mConsoleThreshold( ELOGLEVEL_INFO ),
      mFileThreshold( ELOGLEVEL_DEBUG ),
      mAtLineStart( true ),
      mLogLevel( mDefaultLogLevel ),
      mModuleName( mDefaultModuleName )
{
     std::basic_streambuf<C,T>::setp( &mpInternalBuffer[0], &mpInternalBuffer[BUFFER_SIZE] );
}

/**
 * Destructor. Destroys its internal buffer array
 */
template<typename C, typename T>
DebugStreambuf<C,T>::~DebugStreambuf()
{
    DeleteArray( mpInternalBuffer );
}

/**
 * Set the minimum severity level required before a log entry gets written
 * to the user's console
 */
template<typename C, typename T>
void DebugStreambuf<C,T>::setConsoleThreshold( ELogLevel logLevel )
{
    mConsoleThreshold = logLevel;
}

/**
 * Set the minimum severity level required before a log entry gets written
 * to the log file
 */
template<typename C, typename T>
void DebugStreambuf<C,T>::setFileThreshold( ELogLevel logLevel )
{
    mFileThreshold = logLevel;
}

/**
 * Set the debug stream's console output to be a pointer to the given stream
 * buffer. Passing in NULL will disable the console output.
 *
 * \param  pConsoleBuffer  Pointer to a basic_streambuf
 */
template<typename C, typename T>
void DebugStreambuf<C,T>::setConsole( std::basic_streambuf<C,T> *pConsoleBuffer )
{
    mpConsoleBuffer = pConsoleBuffer;
}

/**
 * Sets the debug stream's file output to be a pointer to the given stream
 * buffer. Passing in NULL will disable the debug log's file output.
 *
 * \param  pFileBuffer  Pointer to a basic_filebuf
 */
template<typename C, typename T>
void DebugStreambuf<C,T>::setFile( std::basic_filebuf<C,T> *pFileBuffer )
{
    mpFileBuffer = pFileBuffer;
}

/**
 * Starts a new log entry
 */
template<typename C, typename T>
void DebugStreambuf<C,T>::startLogEntry( ELogLevel logLevel, const char* moduleName )
{
    // Save this entry's log level and module name before writing the log header
    mLogLevel   = logLevel;
    mModuleName = moduleName;
    
    // Now create the log header
    if ( mpConsoleBuffer != NULL )
    {
        writeEntryHeaderConsole();
    }

    if ( mpFileBuffer != NULL )
    {
        writeEntryHeaderFile();
    }
}

/**
 * Called when the logger has finished emitting a single log entry. This
 * method then resets our internal state in preparation for the next log
 * entry
 */
template<typename C,typename T>
void DebugStreambuf<C,T>::endLogEntry()
{
    // Reset current log entry state
    mAtLineStart = true;
    mLogLevel    = mDefaultLogLevel;
    mModuleName  = mDefaultModuleName;

    // Add a newline character to separate log entries (both for the console
    // and the file)
    std::basic_streambuf<C,T>::sputc( '\n' );

    // Write all buffered log data (this should be all of the current log entry
    // unless it was exceptionally large) to our output sources
     std::basic_streambuf<C,T>::pubsync();
}

/**
 * Called by the underlying basic_streambuf class when it runs out of buffer space
 * to store current log text. This method will drain any text in the internal
 * buffer, and then inform the base streambuf class that we have an empty buffer
 * to use.
 */
template<typename C, typename T>
int DebugStreambuf<C,T>::overflow( int c )
{
    // How much data do we have buffered?
    std::streamsize n = static_cast<std::streamsize>( this->pptr() - this->pbase() );

    // First copy our internal buffer to the console stream
    if ( mpConsoleBuffer != NULL )
    {
        std::streamsize count = mpConsoleBuffer->sputn( this->pbase(), n );

        if ( count != n )
        {
            return traits_type::eof();
        }
    }

    // Now again copy the internal buffer, but this time to our file log
    if ( mpFileBuffer != NULL )
    {
        std::streamsize count = mpFileBuffer->sputn( this->pbase(), n );

        if ( count != n )
        {
            return traits_type::eof();
        }
    }

    // Reset out character buffer
    std::basic_streambuf<C,T>::setp( mpInternalBuffer, mpInternalBuffer + BUFFER_SIZE );

    // Write the passed character (if necessary)
    if (! traits_type::eq_int_type( c, traits_type::eof() ) )
    {
        traits_type::assign( *this->pptr(), traits_type::to_char_type(c) );
        this->pbump( 1 );
    }

    return traits_type::not_eof(c);
}

/**
 * Overridden sync method. When called, this method will synchronize the state
 * of the logger's internal buffer with its output streams (console and file).
 * This will effectively drain all cached text and make it appear.
 */
template<typename C, typename T>
int DebugStreambuf<C,T>::sync()
{
    int retval = 0;

    // drain our internal buffer into mpConsole and mpFile
    int_type c = this->overflow( traits_type::eof() );

    // don't flush if overflow returned an eof
    if ( traits_type::eq_int_type( c, traits_type::eof() ) )
    {
        retval = -1;
    }
    else
    {
        if ( mpConsoleBuffer != NULL && mpConsoleBuffer->pubsync() == -1 )
        {
            retval = -1;
        }

        if ( mpFileBuffer != NULL && mpFileBuffer->pubsync() == -1 )
        {
            retval = -1;
        }
    }

    // Let caller know if we sync'd
    return retval;
}

/**
 * Writes a string directly to the debug buffer
 */
template<typename C, typename T>
void DebugStreambuf<C,T>::write( const std::basic_string<C,T>& str )
{
    sputn( str.c_str(), str.size() );
}

/**
 * Writes the log entry's "header" text out to the console. This text
 * consists of the current date/time, entry module and severity level.
 *
 * \return  True if the header was written to the console, false otherwise
 */
template<typename C, typename T>
bool DebugStreambuf<C,T>::writeEntryHeaderConsole() const
{
    ASSERT_MSG( mpConsoleBuffer != NULL, "Cannot write to null console buffer" );

    // Get the string form of the log level as well as the current
    // time before writing the log entry header
    const size_t TIME_STR_LEN = 10;
    char timeString[TIME_STR_LEN];

    time_t currentTime  = std::time( NULL );

    std::strftime( timeString, TIME_STR_LEN,
                   "%H:%M:%S",
                   localtime(&currentTime) );

    // Generate the log entry header before we hand it over to our
    // underlying buffer object
    const size_t BUFFER_LEN = 32;
    char bufferString[BUFFER_LEN];

#ifdef _WIN32
    int length = _snprintf( bufferString, BUFFER_LEN,
                            "%8s [%c %-12s] ",
                            timeString,
                            getLogLevelString( mLogLevel )[0],
                            mModuleName );
#else
    int length = snprintf( bufferString, BUFFER_LEN,
                           "%8s [%c %-12s] ",
                           timeString,
                           getLogLevelString( mLogLevel )[0],
                           mModuleName );
#endif

    // Now write the header text out to the underlying buffer
    mpConsoleBuffer->sputn( bufferString, length );
    return true;
}

/**
 * Writes the log entry's "header" text out to the file log. This text
 * consists of the current date/time, entry module and severity level.
 *
 * \return  True if the header was written to the file, false otherwise
 */
template<typename C, typename T>
bool DebugStreambuf<C,T>::writeEntryHeaderFile() const
{
    ASSERT_MSG( mpFileBuffer != NULL, "Cannot write to null file buffer" );

    // Get the string form of the log level as well as the current
    // time before writing the log entry header
    const size_t TIME_STR_LEN = 20;
    char timeString[TIME_STR_LEN];

    time_t currentTime  = std::time( NULL );

    std::strftime( timeString, TIME_STR_LEN,
                   "%Y.%m.%d-%H:%M:%S",
                   localtime(&currentTime) );

    // Generate the log entry header before we hand it over to our
    // underlying buffer object
    const size_t BUFFER_LEN = 48;
    char bufferString[BUFFER_LEN];

#ifdef _WIN32
    int length = _snprintf( bufferString, BUFFER_LEN,
                            "%s %s %s ",
                            timeString,
                            getLogLevelString( mLogLevel ),
                            mModuleName );
#else
    int length = snprintf( bufferString, BUFFER_LEN,
                           "%s %s %s ",
                           timeString,
                           getLogLevelString( mLogLevel ),
                           mModuleName );
#endif

    // Now write the header text out to the underlying buffer
    mpFileBuffer->sputn( bufferString, length );
    return true;
}

/**
 * Returns the string name of a given severity level
 */
template<typename C, typename T>
const char* DebugStreambuf<C,T>::getLogLevelString( ELogLevel level ) const
{
    switch ( level )
    {
        case ELOGLEVEL_TRACE:
            return "TRACE";
        case ELOGLEVEL_DEBUG:
            return "DBG";
        case ELOGLEVEL_INFO:
            return "INFO";
        case ELOGLEVEL_NOTICE:
            return "NOTE";
        case ELOGLEVEL_WARN:
            return "WARN";
        case ELOGLEVEL_ERROR:
            return "ERROR";
        case ELOGLEVEL_FATAL:
            return "FATAL";
        case ELogLevel_Count:
        default:
            ASSERT_MSG( false, "Unknown enumeration value for ELogLevel" );
    }

    return "???";
}

#endif

