#ifndef SCOTT_COMMON_REFTAG_H
#define SCOTT_COMMON_REFTAG_H

#include <unordered_map>

typedef unsigned int reftag_id_t;

class RefTag
{
public:
    RefTag( const SymbolTable& owner, reftag_id_t id );
    RefTag( const RefTag& rt );

    std::string name() const;
    reftag_id_t id() const;

    bool operator == ( const RefTag& rhs ) const;
    bool operator != ( const RefTag& rrhs ) const;

private:
    const SymbolTable& mSymbolTable;
    reftag_id_t mId;
};

class SymbolTable
{
public:
    SymbolTable();
    ~SymbolTable();

    RefTag create( const std::string& name );
    RefTag create( const std::string& name, unsigned int suffix );
    RefTag assign( const std::string& name, reftag_id_t id );
    RefTag exists( const std::string& name );
    RefTag exists( reftag_id_t id );
    RefTag find( const std::string& name );
    RefTag find( reftag_id_t id );

private:
    std::unordered_map< reftag_id_t, RefTag > mRefTagDataStore;
    std::unordered_map< std::string, reftag_id_t > mRefTagNameMap;
    reftag_id_t mNextId;
};

#endif
