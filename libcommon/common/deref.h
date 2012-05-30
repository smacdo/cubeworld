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
#ifndef SCOTT_COMMON_DEREF_H
#define SCOTT_COMMON_DEREF_H

#include <common/assert.h>
#include <memory>

/**
 * Returns a non-null reference that refers to the given pointer's address,
 * after performing a checking that the pointer passed is not null.
 *
 * \param  ptr  The constant pointer to dereference
 * \return      A constant reference to the pointer's address
 */
template<typename T>
inline const T& deref( const T* ptr )
{
    assert2( ptr != NULL, "Pointer was null when dereferencing"  );
    return *ptr;
}

/**
 * Returns a non-null reference that refers to the given pointer's address,
 * after performing a checking that the pointer passed is not null.
 *
 * \param  ptr  The pointer to dereference
 * \return      A reference to the pointer's address
 */
template<typename T>
inline T& deref( T* ptr )
{
    assert2( ptr != NULL, "Pointer was null when dereferencing" );
    return *ptr;
}

/**
 * Returns a non-null reference that refers to the given pointer's address,
 * after performing a checking that the pointer passed is not null.
 *
 * \param  sharedPtr  The shared pointer to dereference
 * \return            A reference to the pointer's address
 */
template<typename T>
inline T& deref( std::shared_ptr<T> sharedPtr )
{
    T* ptr = sharedPtr.get();
    assert( ptr != NULL );

    return *ptr;
}

#endif
