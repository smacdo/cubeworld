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
#include "app/logging.h"
#include "app/logging_debugstreambuf.h"
#include "app/logging_stream.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * Logstream constructor
 */
LogStream::LogStream( std::ostream *pConsoleStream,
                      std::ofstream *pFileStream )
    : std::ios( 0 ),
      std::ostream( new DebugStreambuf<char> ),
      mpStreambuf( NULL ),
      mpConsoleStream( pConsoleStream ),
      mpFileStream( pFileStream )
{
    // i really don't like having to do this
    mpStreambuf = dynamic_cast<DebugStreambuf<char>* >( rdbuf() );
    assert( mpStreambuf != NULL && "Something really evil just happened" );

    // Assign the output streams to our internal debug stream
    if ( pConsoleStream != NULL )
    {
        mpStreambuf->setConsole( pConsoleStream->rdbuf() );
    }

    if ( pFileStream != NULL )
    {
        mpStreambuf->setFile( pFileStream->rdbuf() );
    }
}

/**
 * Log stream destructor. Closes all the streams that the debug stream object
 * is writing to
 */
LogStream::~LogStream()
{
    // Destroy the log stream's internal stream buffer
    delete mpStreambuf;

    // Make sure we close the current file stream
    if ( mpFileStream != NULL )
    {
        mpFileStream->close();
    }
}

/**
 * Sets a new console output stream. This assumes that the ostream being passed
 * is either a STDOUT/STDERR/STDLOG stream or is a stream that is being managed
 * by another part of the codebase.
 *
 * Any console stream associated to this log will NOT be closed when the log stream
 * is destroyed.
 */
void LogStream::setConsoleStream( std::ostream *pConsoleStream )
{
    mpConsoleStream = pConsoleStream;

    if ( pConsoleStream != NULL )
    {
        mpStreambuf->setConsole( pConsoleStream->rdbuf() );
    }
    else
    {
        mpStreambuf->setConsole( NULL );
    }
}

/**
 * Sets a new file stream for the logger. This file will receive log entries that
 * are custom formatted for file output, and will be closed when no longer
 * needed.
 */
void LogStream::setFileStream( std::ofstream *pFileStream )
{
    // If there is an active file stream, close it before proceeding
    if ( mpFileStream != NULL )
    {
        mpFileStream->close();
    }

    // Now make this file stream be the log's new file output stream
    mpFileStream = pFileStream;

    if ( mpFileStream != NULL )
    {
        mpStreambuf->setFile( pFileStream->rdbuf() );
    }
    else
    {
        mpStreambuf->setFile( NULL );
    }
}

/**
 * Starts a new log entry
 */
void LogStream::startLogEntry( const std::string& system, ELogLevel level )
{
    mpStreambuf->startLogEntry( level, system.c_str() );
}

/**
 * Ends the correct log entry
 */
void LogStream::endLogEntry()
{
    mpStreambuf->endLogEntry();
}

