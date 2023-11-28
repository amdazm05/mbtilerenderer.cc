#include <vectortilecodec.hpp>

namespace vector_tile
{
    VectorTileCodec::VectorTileCodec()
    {

    }
    VectorTileCodec::~VectorTileCodec()
    {

    }
    vector_tile::Tile_Feature VectorTileCodec::Decode(std::size_t zoom,
        std::size_t column,std::size_t row ,std::string & s)
    {
        vector_tile::Tile tileData;
        bool check = tileData.ParseFromString(s);
        if(check)
            std::runtime_error("VectorTileCodec: Tile Parsing Failed ");
        std::size_t layer_count = tileData.layers_size();
        auto & layers = tileData.layers();
        for(auto & layer : layers)
        {
            // version of tile should be consistent do not proceed if otherwise or skip the tile if needed 
            // A vector tile must have atleast 1 layer 
            // Layer names must not be identical, byte by byte comparison
            auto & features = layer.features();  
            for(auto & feature:features)
            {
                // Each feature in a layer (see below) may have one or more key-value pairs as its metadata.
                //  The set of keys SHOULD NOT contain two or more values which are byte-for-byte identical.

                // A feature MUST contain a geometry field.
                // A feature MUST contain a type field as described in the Geometry Types section.
                // A feature MAY contain a tags field. Feature-level metadata, if any, SHOULD be stored in the tags field.
                // A feature MAY contain an id field. If a feature has an id field, the value of the id SHOULD be unique among the features of the parent layer.
                
                std::vector<std::pair<int,int>> points;
                for(auto & geometry: feature.geometry())
                {
                    // geometry field of a feature. Each integer is either a CommandInteger or a ParameterInteger

                    // Command Integers: (Formulated using (id & 0x7)
                    // move to    1
                    // line to    2
                    // close path 7
                    CommandIntegers id = (CommandIntegers)(geometry & 0x7);
                    uint32_t count = geometry >>3;
                    auto featuretype = feature.type(); 
                    switch(id)
                    {
                        case CommandIntegers::MOVE_TO:
                            break;
                        case CommandIntegers::LINE_TO: 
                            break;
                        case CommandIntegers::CLOSE_PATH:
                            break; 
                        default:
                            // Do nothing corrupted tile
                            break;
                    }
                }

            }
        }

        return {};
    }

}