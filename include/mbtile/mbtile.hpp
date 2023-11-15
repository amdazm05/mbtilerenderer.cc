#ifndef _MBTILE
#define _MBTILE

#include <iostream>
#include <memory>
#include <vector>
#include <utility>

namespace mbtile
{
    class tile_t
    {
        public:
            std::size_t tile_col;
            std::size_t tile_row;
            std::shared_ptr<uint8_t> bitmap_image;
        public:
            /// @brief Constructors
            tile_t():tile_t(0,0){}
            tile_t(std::size_t tile_col,std::size_t tile_row):
                tile_col(tile_col),
                tile_row(tile_row)
            {}
    };

    class tilezoom_t
    {
        public:
            std::vector<tile_t> tiles;
            std::size_t zoom_level;
        public:
            /// @brief Constructors
            tilezoom_t():tilezoom_t(0){}
            tilezoom_t(std::size_t zoom_level):
                zoom_level(zoom_level){}
    };
}

#endif //_MBTILE