#ifndef _MB_TILE_CACHER
#define _MB_TILE_CACHER

// STL 
#include <iostream>

//Local
#include <SQLiteCpp/SQLiteCpp.h>
#include <mbtile/mbtile.hpp>
#include <util/compressdecompressor.hpp>

class MbTileCacher 
{
    private:
        std::vector<mbtile::tile_t> tilecache_;
        SQLite::Database db;
        SQLite::Statement query_statement_;
    public:
        MbTileCacher()=delete;
        MbTileCacher(std::string && path);
        ~MbTileCacher();
};

#endif //_MB_TILE_CACHER
