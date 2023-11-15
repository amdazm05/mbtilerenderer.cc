#ifndef _MBTILE
#define _MBTILE

#include <iostream>
#include <memory>
#include <vector>

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
            tile_t(tile_t &&t) noexcept: 
                tile_col(std::exchange(t.tile_col,0)),
                tile_row(std::exchange(t.tile_row,0)),
                bitmap_image(t.bitmap_image)
            {}
            tile_t(tile_t &t) noexcept: 
                tile_col(t.tile_col),
                tile_row(t.tile_row)
                bitmap_image(t.bitmap_image)
            {}
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
            tilezoom_t():tile_t(0,0){}
            tilezoom_t(tilezoom_t &&t) noexcept: 
                zoom_level(std::exchange(t.tile_col,0)),
                tiles(t.tiles)
            {}
            tilezoom_t(tilezoom_t &t) noexcept: 
                zoom_level(t.zoom_level),
                tiles(t.tiles)
            {}
            tilezoom_t(std::size_t zoom_level):
                zoom_level(zoom_level),
                tile_row(tile_row)
            {}
    };
}

#endif //_MBTILE