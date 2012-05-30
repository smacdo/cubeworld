/*
 * Copyright 2010-2012 Scott MacDonald
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
#ifndef SCOTT_COMMON_TIME
#define SCOTT_COMMON_TIME

#include <string>

/**
 * Class used to measure and keep track of arbitrary amounts of time.
 * The time class measures time in terms of seconds, and has no pre-defined
 * start time.
 *
 * (eg, 5 seconds does not mean 5 seconds since epoch. It is just
 *  "five seconds").
 */
class Time
{
public:
    Time();
    Time( const Time& t );
    explicit Time( int seconds );
    explicit Time( float seconds );
    explicit Time( double seconds );

    static Time fromNanoSeconds( unsigned int time );
    static Time fromMilliSeconds( unsigned int time );
    static Time fromMicroSeconds( unsigned int time );

    unsigned int minutes() const;
    unsigned int seconds() const;
    std::string toString() const;

    Time& operator = ( const Time& rhs );

    bool operator == ( const Time& rhs ) const;
    bool operator != ( const Time& rhs ) const;
    bool operator <  ( const Time& rhs ) const;
    bool operator <= ( const Time& rhs ) const;
    bool operator >  ( const Time& rhs ) const;

    Time  operator +  ( const Time& rhs ) const;
    Time& operator += ( const Time& rhs );

    Time  operator -  ( const Time& rhs ) const;
    Time& operator -= ( const Time& rhs );

    const static double TimeDelta;
private:
    double mSeconds;
};

#endif
