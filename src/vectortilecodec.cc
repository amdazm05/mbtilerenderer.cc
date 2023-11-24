#include <vectortilecodec.hpp>

namespace vector_tile
{
    VectorTileCodec::VectorTileCodec()
    {

    }
    VectorTileCodec::~VectorTileCodec()
    {

    }
    vector_tile::Tile_Feature VectorTileCodec::Decode(std::string & s)
    {
        vector_tile::Tile tileData;
        bool check = tileData.ParseFromString(s);
        if(!check)
            throw std::runtime_error("Tile Parsing Failed");

        std::size_t layer_count = tileData.layers_size();
        for(auto & layer : tileData.layers())
        {
            std::cout<<layer.version()<<" "<<layer.name()<<" "<<layer.extent()<<std::endl;
        }

        return {};
    }

}