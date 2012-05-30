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
#ifndef SCOTT_COMMON_ASSERT_H
#define SCOTT_COMMON_ASSERT_H

// Check for presence of the NDEBUG macro. If it exists, the built in
// assertion will be disabled. There's no good way to go about manually
// disabling the builtin assertion macro, so we must rely on NDEBUG turning
// it off.
//
// Long story short: This file's custom assert cannot coexist with builtin
// assert. Turn it off
#ifndef NDEBUG
#   error "Builtin assert(x) enabled. Disable it with NDEBUG for custom asserts"
#endif

// If the compiler's debug mode is enabled, then turn on assertions.
// TODO: Make this more robust
#if defined(_DEBUG)
#   define ASSERTS_ENABLED  1
#   define ASSERTS_VERIFY   1
#endif

// Define the platform specific way of generating a debugger trap
#ifdef _MSC_VER
#   define assert_break __debugbreak()
#else
#   define assert_break __builtin_trap()
#endif

//
// Assertion handling methods
//
namespace Debug
{
    enum EAssertionStatus
    {
        EAssertion_Halt,
        EAssertion_Continue
    };

    typedef EAssertionStatus (*assertionHandler)(const char*,
                                                 const char*,
                                                 const char*,
                                                 unsigned int );

    // Install a custom assertion handler
    void setAssertionHandler( assertionHandler handler );

    // Raises a software assertion
    EAssertionStatus raiseAssertion( const char *pMessage,
                                     const char *pExpression,
                                     const char *pFile,
                                     unsigned int line );

    // Places the application into unit test mode
    void setInUnitTestMode( bool isInUnitTestMode );

    // Tells unit tester if we should allow program to keep running
    void setTestAssertShouldDie( bool shouldDie );

    // Reset default behavior
    void resetTestAssertShouldDie();
};

//
// Custom assertion handling
//
#ifdef ASSERTS_ENABLED
#   define scott_assert(msg,cond)           \
    do                                      \
    {                                       \
        if ( !(cond) )                      \
        {                                   \
            if ( Debug::raiseAssertion(msg,#cond,__FILE__,__LINE__) == \
                 Debug::EAssertion_Halt )   \
                assert_break;               \
        }                                   \
    } while( 0 )
#   define assert2(expr,msg) scott_assert(msg,expr)
#   define assert_null(var) scott_assert("Pointer was expected to be null",#var##" == NULL")
#   define assert_notNull(var) scott_assert("Pointer was expected to be non-null",#var##" != NULL")

#   ifdef ASSERTS_VERIFY        // only enabled for full sanity checks
#       define verify(expression)  scott_assert(NULL,expression)
#   else
#       define verify(expression)  do { (void)sizeof(x); } while(0)
#   endif
#   ifdef assert
#       undef assert
#   endif
#   define assert(x) scott_assert(NULL,x)
#else
#   ifndef assert
#       define assert(x)          do { (void)sizeof(x); } while(0)
#   endif
#   define assert2(x,m)       do { (void)sizeof(x); } while(0)
#   define assert_null(x)     do { (void)sizeof(x); } while(0)
#   define assert_notNull(x)  do { (void)sizeof(x); } while(0)
#   define verify(x)          do { (void)sizeof(x); } while(0)
#endif

#endif
