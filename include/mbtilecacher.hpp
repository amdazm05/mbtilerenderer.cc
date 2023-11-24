#ifndef _MB_TILE_CACHER
#define _MB_TILE_CACHER

// STL 
#include <iostream>
#include <memory>
//DS
#include <datastructures/lrucache.tpp>

//Local
#include <SQLiteCpp/SQLiteCpp.h>
#include <mbtile/mbtile.hpp>
#include <util/compressdecompressor.hpp>

namespace mbtile
{
    /// @brief A class that contains references to map tiles
    /// This should be complemented as being an LRU cache
    class MbTileCacher : std::enable_shared_from_this<MbTileCacher>
    {
        private:
            SQLite::Database db_;
            utils::ComDecompressor comdecomObj_;
            lru_cache<std::string,mbtile::tile_t> lrucache_;
        public:
            MbTileCacher()=delete;
            MbTileCacher(std::string && path);
            ~MbTileCacher();
            bool query_tile(std::size_t zoomlevel,std::size_t x,std::size_t y);
    };
}

// Cache recently used tiles and not all searched in the DB
//Implementing our own LRU cache
// std::vector<mbtile::tile_t> tilecache_;
// Great Article
// https://stackoverflow.com/questions/36822571/when-we-should-use-lru-cache-is-this-a-best-solution
#endif //_MB_TILE_CACHER
