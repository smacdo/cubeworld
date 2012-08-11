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

//---------------------------------------------------------------------------
// The following macro defines affect assertion functionality
//
//   - DISABLE_ASSERTS: ASSERT is compiled out and never executed
//   - ENABLE_ASSERT_HANDLER: Allows custom assertion reporting. If disabled,
//                            asserts are handed to the standard ::assert(EXPR)
//   - NDEBUG: Always disables assertions, both ASSERT and assert
//
// Parts of this file are heavily inspired from boost's assert.hpp
//----------------------------------------------------------------------------
// Undefine our assert macros, in case someone already defined them (BAD!)
#undef ASSERT
#undef ASSERT_MSG
#undef VERIFY

// Define the platform specific way of generating a debugger trap
#ifdef _MSC_VER
#   define assert_break __debugbreak()
#else
#   define assert_break __builtin_trap()
#endif

//
// ASSERT - replacement for the system assert(expr) macro. This custom macro
// adds additional error reporting functionality, including the ability to
// install a custom assert handler
//
#if defined( DISABLE_ASSERTS ) || defined( NDEBUG )
#   define ASSERT(expr) ((void)0)
#elif defined( ENABLE_ASSERT_HANDLER )
#   include <miniboost/current_function.hpp>
#   define ASSERT(expr)                     \
    do                                      \
    {                                       \
        if ( !(expr) )                      \
        {                                   \
            if ( Assert::raiseAssertion(#expr,NULL,BOOST_CURRENT_FUNCTION,__FILE__,__LINE__) ) \
                assert_break;               \
        }                                   \
    } while( 0 )
#else
#   define ASSERT(expr) assert(expr)
#endif

//
// ASSERT_MSG - Similiar to the ASSERT macro, but the second statement allows
// the developer to specify an error message that is displayed when the
// assertion fails
//
#if defined( DISABLE_ASSERTS ) || defined( NDEBUG )
#   define ASSERT_MSG(expr, msg) ((void)0)
#elif defined( ENABLE_ASSERT_HANDLER )
#   define ASSERT_MSG(expr,msg)             \
    do                                      \
    {                                       \
        if ( !(expr) )                      \
        {                                   \
            if ( Assert::raiseAssertion(#expr,msg,BOOST_CURRENT_FUNCTION,__FILE__,__LINE__) ) \
                assert_break;               \
        }                                   \
    } while( 0 )
#else
#   error WTF
#   define ASSERT_MSG(expr,msg) ASSERT(expr && (msg))
#endif

//
// VERIFY - Identical to ASSERT, except that it is not compiled out in release
// mode.
//
// (It will be disabled if DISABLE_ASSERTS is defined, OR NDEBUG is turned on
// AND ENABLE_ASSERT_HANDLER is disabled)
//
#if defined(DISABLE_ASSERTS) || ( !defined(ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )
#   define VERIFY(expr) ((void)(expr))
#else
#   define VERIFY(expr) ASSERT(expr)
#endif

// Utility ASSERTs
#define CORE_ASSERT(expr,msg) ASSERT_MSG(expr,msg)
#define ASSERT_NULL(var) ASSERT_MSG((var)==NULL,#var " is not null");
#define ASSERT_NOT_NULL(var) ASSERT_MSG((var)!=NULL,#var " is null");

//--------------------------------------------------------------------------//
// Assertion handling routines                                              //
//--------------------------------------------------------------------------//
#ifndef SCOTT_COMMON_ASSERT_H       // we only want this for the function defs
#define SCOTT_COMMON_ASSERT_H

namespace Assert
{
    enum EAssertAction
    {
        EASSERT_EXIT,
        EASSERT_BREAK,
        EASSERT_CONTINUE
    };

    // Assertion handler function callback typedef. Makes passing the
    // function pointer a lot easier
    typedef EAssertAction (*assert_func_t)( const char*,
                                            const char*,
                                            const char*,
                                            const char*,
                                            unsigned int );

    // The default assertion handler, prints to the console and aborts
    bool raiseAssertion( const char * pExpression,
                         const char * pReason,
                         const char * pFunction,
                         const char * pFile,
                         unsigned int pLine );

    // Set a custom assertion handler 
    void setAssertHandler( assert_func_t pAssertHandler );

    // Retrieve the current assertion handler
    assert_func_t getAssertHandler();

    // The default assertion handler, prints to the console and aborts
    EAssertAction defaultAssertHandler( const char * pExpression,
                                        const char * pReason,
                                        const char * pFunction,
                                        const char * pFile,
                                        unsigned int pLine );
}

#endif
