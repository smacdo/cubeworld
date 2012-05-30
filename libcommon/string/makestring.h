
/**
 * void f( const std::string& input );
 *
 * somefunction() {
 *    int number = 42;
 *    f( MakeString() << "The answer is " << number << "!!!" );
 */
class MakeString
{
public:
    template<typename T>
    MakeString& operator << ( const T& data )
    {
        m_buffer << data;
        return *this;
    }

    operator std::string() const
    {
        return m_buffer.str();
    }

private:
    std::ostringstream m_Buffer;
}
