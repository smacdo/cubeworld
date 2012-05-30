#ifndef SCOTT_COMMON_NonCopyable_H
#define SCOTT_COMMON_NonCopyable_H

/**
 * Class NonCopyable is a utility class that one can inherit from to
 * prevent said class from being copied. While it is trivial to do this
 * for a class, it is more explicit when the class inherits from a
 * NonCopyable base.
 */
class NonCopyable
{
protected:
    NonCopyable() { }
    ~NonCopyable() { }

private:
    NonCopyable( const NonCopyable& );
    const NonCopyable& operator = ( const NonCopyable& );
};

#endif
