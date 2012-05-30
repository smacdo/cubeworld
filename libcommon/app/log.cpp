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
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

/**
 * Writes a trace entry to the program's log, and a stream that can be
 * used to append additional information to the entry
 *
 * \param  system  The name of the system or component writing the entry
 * \return A LogEntry object that can be used to append additional
 *         information to the log entry
 */
LogEntry Log::trace( const std::string& system ) const
{
    mDebugStream->startLogEntry( system, ELOGLEVEL_INFO );
    return LogEntry( mDebugStream );
}

/**
 * Writes a debug entry to the program's log, and a stream that can be
 * used to append additional information to the entry
 *
 * \param  system  The name of the system or component writing the entry
 * \return A LogEntry object that can be used to append additional
 *         information to the log entry
 */
LogEntry Log::debug( const std::string& system ) const
{
    mDebugStream->startLogEntry( system, ELOGLEVEL_DEBUG );
    return LogEntry( mDebugStream );
}

/**
 * Writes an info entry to the program's log, and a stream that can be
 * used to append additional information to the entry
 *
 * \param  system  The name of the system or component writing the entry
 * \return A LogEntry object that can be used to append additional
 *         information to the log entry
 */
LogEntry Log::info( const std::string& system ) const
{
    mDebugStream->startLogEntry( system, ELOGLEVEL_INFO );
    return LogEntry( mDebugStream );
}

/**
 * Writes a notice entry to the program's log, and a stream that can be
 * used to append additional information to the entry
 *
 * \param  system  The name of the system or component writing the entry
 * \return A LogEntry object that can be used to append additional
 *         information to the log entry
 */
LogEntry Log::notice( const std::string& system ) const
{
    mDebugStream->startLogEntry( system, ELOGLEVEL_NOTICE );
    return LogEntry( mDebugStream );
}

/**
 * Writes a warning entry to the program's log, and a stream that can be
 * used to append additional information to the entry
 *
 * \param  system  The name of the system or component writing the entry
 * \return A LogEntry object that can be used to append additional
 *         information to the log entry
 */
LogEntry Log::warn( const std::string& system ) const
{
    mDebugStream->startLogEntry( system, ELOGLEVEL_WARN );
    return LogEntry( mDebugStream );
}

/**
 * Sets the output stream used for console window output
 */
void Log::setConsoleStream( std::ostream *pConsoleStream )
{
    if ( pConsoleStream == NULL )
    {
        warn("Logging") << "Attaching a null console stream...";
    }

    mDebugStream->setConsoleStream( pConsoleStream );
}

/**
 * Sets the output stream used for file output
 */
void Log::setFileStream( std::ofstream *pFileStream )
{
    if ( pFileStream == NULL )
    {
        warn("Logging") << "Attaching a null file stream...";
    }

    mDebugStream->setFileStream( pFileStream );
}

/**
 * Writes an error entry to the program's log, and a stream that can be
 * used to append additional information to the entry
 *
 * \param  system  The name of the system or component writing the entry
 * \return A LogEntry object that can be used to append additional
 *         information to the log entry
 */
LogEntry Log::error( const std::string& system ) const
{
    mDebugStream->startLogEntry( system, ELOGLEVEL_ERROR );
    return LogEntry( mDebugStream );
}
