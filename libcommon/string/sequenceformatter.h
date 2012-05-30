#ifndef SCOTT_COMMON_STRING_SEQUENCELISTER_H
#define SCOTT_COMMON_STRING_SEQUENCELISTER_H

#include <iostream>
#include <string>
#include <iterator>

/**
 * Utility to pretty-print containers
 *
 * std::cout << print_sequence( container, ", " ) << std::endl
 */

template<typename T> class SequenceLister;

template<typename Iter>
inline std::ostream& operator << ( std::ostream& os,
                                   const SequenceLister<Iter>& sl )
{
    for ( Iter itr = sl.first; itr != sl.last; ++itr )
    {
        if ( itr != sl.first )
        {
            os << sl.delim;
        }

        os << *itr;
    }

    return os;
}

template<typename Itr>
class SequenceLister
{
public:
    SequenceLister( Itr first_, Itr last_, const char * delim_ = ", " )
        : first( first_ ),
          last( last_ ),
          delim( delim_ )
    {
    }

    /**
     * Constructor supporting generic containers that implement begin()
     * and end()
     */
    template<typename Container>
    SequenceLister( Container& container, const char * delim_ = ", " )
        : first( container.begin() ),
          last( container.end() ),
          delim( delim_ )
    {
    }

    friend std::ostream& operator << <>( std::ostream& os,
                                         const SequenceLister<Itr>& sl );

private:
    // Copy construct disabled
    SequenceLister( const SequenceLister& sl );

    // Assignment disabled
    SequenceLister& operator = ( const SequenceLister& sl );
};

template<typename Itr>
inline SequenceLister<Itr> printSequence( Itr first,
                                          Itr second,
                                          const char * delim = ", " )
{
    return SequenceLister<Itr>( first, second, delim );
}

template<typename Container>
inline SequenceLister<typename Container:const_iterator:> printSequence(
        const Container& container,
        const char * delim = ", " )
{
    return SequenceLister<typename Container::const_iterator>(
            container,
            delim
    );
}
#endif
