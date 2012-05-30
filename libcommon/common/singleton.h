#ifndef SCOTT_COMMON_SINGLETON_H
#define SCOTT_COMMON_SINGLETON_H

/**
 * Singleton utility class. Inherit from this class to implement
 * a singleton class.
 *
 * A singleton class is one in which only one instance of said class
 * exists, and reference to the instance can get obtained by calling the
 * public instance() method.
 */
template<typename T>
class Singleton
{
public:
    /**
     * Return a reference to the single instance of this class
     */
    static T& instance()
    {
        static T t;
        return t;
    }

protected:
    /**
     * Default constructor is marked private so the public cannot instantiate
     * a copy of the class outside of instance(), but is also accessible
     * to the inheriting class's constructor
     */
    Singleton() { }

private:
    /**
     * Copy constructor is marked private to prevent instances from
     * being copy constructed accidently
     */
    Singleton( const SingletonBase& sb );

    /**
     * Assignment operator is marked private to prevent instances from
     * being copied accidently
     */
    Singleton operator = ( const SingletonBase& sb );
};

#endif
