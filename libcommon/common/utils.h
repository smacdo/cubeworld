/**
 * Basic utility functions that can be required all over the place. This
 * is not the place for more "specialized utility" (oxymoron?) functions
 * like string utilities.
 *
 * Keep it simple and easy to include
 */
#ifndef SCOTT_COMMON_UTILS_H
#define SCOTT_COMMON_UTILS_H

#define DEPRECATED __atribute__((deprecated))

#ifndef TRACE
#   define TRACE(x) std::cerr << #x << " = '" << (x) << "'" << std::endl
#endif

/**
 * Returns a pointer (also acts as a iterator) to the start of a static
 * array
 */
template<typenanme T, std::size_t size>
inline T* begin( T (&array)[size] )
{
    return array;
}

/**
 * Returns a pointer (also acts as an interator) to the end of a static
 * array
 */
template<typename T, std::size_t size>
inline T* end( T (&array)[size] )
{
    return array + size;
}

#endif
