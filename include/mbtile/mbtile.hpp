#ifndef _MBTILE
#define _MBTILE

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <unordered_map>

namespace mbtile
{
    class tile_t
    {
        public:
            std::size_t tile_col;
            std::size_t tile_row;
            std::size_t zoom_level;
            std::shared_ptr<char> pbtile;
        public:
            /// @brief Constructors
            tile_t():tile_t(0,0,0){}
            tile_t(std::size_t tile_col,std::size_t tile_row,std::size_t zoom_level):
                tile_col(tile_col),
                tile_row(tile_row),
                zoom_level(zoom_level)
            {}
    };

    class tiledef_t
    {
        public:
            std::unordered_map<std::size_t,tile_t> umap;
        public:
            /// @brief Constructors
            tiledef_t(){}
    };
}

#endif //_MBTILE