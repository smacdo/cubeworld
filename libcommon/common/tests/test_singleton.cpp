#include <googletest/googletest.h>
#include <common/singleton.h>

class Foo : public Singleton<Foo>
{
public:
    void set( int v )
    {
        shared = v;
    }

    int get() const
    {
        return shared;
    }

private:
    static int shared;
};

int Foo::shared = 0;


TEST(SingletonTests,SameObjectReturned)
{
    // Load the pointer returned by our instance
    Foo * pF = NULL;

    {
        Foo& f = Foo::instance();
        pF     = &f;

        EXPECT_TRUE( pF != NULL );
    }

    // Verify that the pointer has not changed when returned again
    {
        Foo& f = Foo::instance();
        EXPECT_EQ( pF, &f );
    }
}

TEST(SingletonTests,StaticPersistsAcrossCalls)
{
    // Check initial value, and set a shared value
    {
        Foo& f = Foo::instance();
        EXPECT_EQ( 0, f.get() );
    
        f.set( 42 );
    }

    // Get a new reference, verify that the value was saved
    {
        Foo& f = Foo::instance();
        EXPECT_EQ( 42, f.get() );
    }
}
