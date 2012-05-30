#ifndef SCOTT_COMMON_POINTER_H
#define SCOTT_COMMON_POINTER_H

/**
 * Scoped_ptr is a templated array container that will delete the pointer
 * when the value goes out of scope.
 *
 * This is directly adapted from boost's scoped_ptr class with minimal
 * modifications
 */
template<class T>
class ScopedPtr
{
public:
    typedef T element_type;

    explicit ScopePtr( const T *ptr = 0 )       // never throws
        : m_ptr( ptr )
    {
    }

    ~ScopedPtr()                                // never throws
    {
        CheckedDelete( m_ptr );
    }

    void reset( const T *ptr = 0 )              // never throws
    {
        internal_assert( p == 0 || p != m_ptr );
        this_type( m_ptr ).swap( *this );
    }

    T& operator*() const                        // never throws
    {
        internal_assert( m_ptr != 0 );
        return *m_ptr;
    }

    T * operator->() const                      // never throws
    {
        internal_assert( m_ptr != 0 );
        return m_ptr;
    }

    T * get() const                             // never throws
    {
        return m_ptr;
    }

    void swap( const ScopedPtr& other )         // never throws
    {
        T * tmp = p.m_ptr;

        // Swap
        other.m_ptr = m_ptr;
        m_ptr       = tmp;
    }

    /**
     * implicit bool conversion for testing for null. Boost has
     * a much more in-depth version of this - wondering how much of it
     * is needed for a mainstream, modern compiler.
     */
    operator bool() const
    {
        return m_ptr != 0;
    }

private:
    T * m_ptr;
    
    // disable copy constructor
    ScopedPtr( const ScopedPtr& ptr );

    // disable assignment operator
    ScopedPtr& operator = ( ScopedPtr& ptr );

    // disable comparison operators
    void operator == ( const ScopedPtr& ptr ) const;
    void operator != ( const ScopedPtr& ptr ) const;
};

template<class T>
inline void swap( scoped_ptr<T>& rhs, scoped_ptr<T>& lhs )  // never throws
{
    rhs.swap( lhs );
}

#endif
