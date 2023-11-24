#ifndef _VECTOR_TILE
#define _VECTOR_TILE
#include <memory>
#include <string>
#include <vector_tile.pb.h>
/// @brief  Scope
///       - 

namespace vector_tile
{
    class VectorTileCodec:std::enable_shared_from_this<VectorTileCodec>
    {
        public:
            VectorTileCodec();
            ~VectorTileCodec();
            vector_tile::Tile_Feature Decode(std::string & s);
            // Not in V0.0 Scope right now
            // void Encode()
    };
}

#endif //_VECTOR_TILE