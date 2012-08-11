#ifndef SCOTT_COMMON_POINTER_H
#define SCOTT_COMMON_POINTER_H

#include <common/assert.h>
#include <common/delete.h>

// Forward declarations
template<class T> class scoped_ptr;
template<class T> inline void swap( scoped_ptr<T>& rhs, scoped_ptr<T>& lhs );

/**
 * Scoped_ptr is a templated array container that will delete the pointer
 * when the value goes out of scope.
 *
 * This is directly adapted from boost's scoped_ptr class with minimal
 * modifications
 */
template<class T>
class scoped_ptr
{
public:
    typedef T element_type;

    explicit scoped_ptr( T *ptr = 0 )       // never throws
        : mPtr( ptr )
    {
    }

    ~scoped_ptr()                                // never throws
    {
        Delete( mPtr );
    }

    void reset( const T *ptr = 0 )              // never throws
    {
        if ( ptr != mPtr )
        {
            Delete( mPtr );
            mPtr = ptr;
        }
    }

    T& operator*() const                        // never throws
    {
        CORE_ASSERT( mPtr != 0, "Cannot dereference a null scoped pointer" );
        return *mPtr;
    }

    T * operator->() const                      // never throws
    {
        CORE_ASSERT( mPtr != 0, "Cannot dereference a null scoped pointer" );
        return mPtr;
    }

    T * get() const                             // never throws
    {
        return mPtr;
    }

    void swap( scoped_ptr& other )         // never throws
    {
        T * tmp = other.mPtr;

        // Swap
        other.mPtr = mPtr;
        mPtr       = tmp;
    }

    /**
     * implicit bool conversion for testing for null. Boost has
     * a much more in-depth version of this - wondering how much of it
     * is needed for a mainstream, modern compiler.
     */
    operator bool() const
    {
        return mPtr != 0;
    }

private:
    T * mPtr;
    
    // disable copy constructor
    scoped_ptr( const scoped_ptr& ptr );

    // disable assignment operator
    scoped_ptr& operator = ( scoped_ptr& ptr );

    // disable comparison operators
    void operator == ( const scoped_ptr& ptr ) const;
    void operator != ( const scoped_ptr& ptr ) const;
};

template<class T>
inline void swap( scoped_ptr<T>& rhs, scoped_ptr<T>& lhs )  // never throws
{
    rhs.swap( lhs );
}

#endif
