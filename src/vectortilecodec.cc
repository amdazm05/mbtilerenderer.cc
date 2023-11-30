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
        if(!check)
            throw std::runtime_error("VectorTileCodec: Tile Parsing Failed ");
        
        uint32_t tile_count = 1<<zoom;
        minlonglatextents_ = utils::tile_to_latlong(row+1,column, zoom);
        maxlonglatextents_ = utils::tile_to_latlong(row,column+1, zoom);
        diffboundslatlong_.first  = minlonglatextents_.first - minlonglatextents_.first;
        diffboundslatlong_.second = maxlonglatextents_.second - maxlonglatextents_.second;  
        std::pair<int,int> cursor_p={0,0};
        std::size_t layer_count = tileData.layers_size();

        for(std::size_t layerIndex = 0;layerIndex<tileData.layers_size();layerIndex++)
        {
            // version of tile should be consistent do not proceed if otherwise or skip the tile if needed 
            // A vector tile must have atleast 1 layer 
            // Layer names must not be identical, byte by byte comparison
            auto & layer = tileData.layers(layerIndex);
            uint32_t extent = layer.extent(); 
            for(std::size_t featureIndex = 0;featureIndex<layer.features_size();featureIndex++)
            {
                auto feature = layer.features(featureIndex);
                // Each feature in a layer (see below) may have one or more key-value pairs as its metadata.
                //  The set of keys SHOULD NOT contain two or more values which are byte-for-byte identical.

                // A feature MUST contain a geometry field.
                // A feature MUST contain a type field as described in the Geometry Types section.
                // A feature MAY contain a tags field. Feature-level metadata, if any, SHOULD be stored in the tags field.
                // A feature MAY contain an id field. If a feature has an id field, the value of the id SHOULD be unique among the features of the parent layer.
                
                for(std::size_t geometryIndex = 0;geometryIndex<feature.geometry_size();geometryIndex++)
                {
                    // geometry field of a feature. Each integer is either a CommandInteger or a ParameterInteger
                    uint32_t geometry = feature.geometry(geometryIndex);
                    // Command Integers: (Formulated using (id & 0x7)
                    // move to    1
                    // line to    2
                    // close path 7
                    CommandIntegers id = (CommandIntegers)(geometry & 0x7);
                    uint32_t commandCount = geometry >>3;
                    auto featuretype = feature.type(); 
                    // (cX, cY) where cX is the position of the cursor on the X axis and cY
                    // (pX, pY), where pX = cX + dX and pY = cY + dY
                        // Within POINT geometries, this coordinate defines a new point.
                        // Within LINESTRING geometries, this coordinate defines the starting vertex of a new line.
                        // Within POLYGON geometries, this coordinate defines the starting vertex of a new linear ring.
                    switch(id)
                    {
                        case CommandIntegers::MOVE_TO:
                        for(std::size_t i=0;i<commandCount;i++)
                        {
                            //https://github.com/mapbox/vector-tile-spec/tree/master/2.1#432-parameter-integers
                            if(i+2>feature.geometry_size()) break;
                            uint32_t  value1 = feature.geometry(geometryIndex+1);
                            uint32_t  value2 = feature.geometry(geometryIndex+2);
                            
                            // A ParameterInteger is zigzag encoded so that small negative and positive values are both encoded as small integers
                            int32_t parameterInteger1 =  (value1 << 1) ^ (value1>> 31);
                            int32_t parameterInteger2 =  (value2 << 1) ^ (value2>> 31);

                            //dx, dy are parameters 1 and 2 
                            cursor_p.x+=parameterInteger1;
                            cursor_p.y+=parameterInteger2;
                            std::pair<double,double> point = 
                            {
                                diffboundslatlong_.second * double(cursor_p.x) / double(extent) + minlonglatextents_.second,
                                diffboundslatlong_.first * double(cursor_p.y) / double(extent) + minlonglatextents_.first
                            };
                            
                            if(featuretype==vector_tile::Tile_GeomType_POINT)
                                points_.push_back(point);
                            geometryIndex+=2;
                        }
                        break;
                        case CommandIntegers::LINE_TO: 
                            for(std::size_t i=0;i<commandCount;i++)
                            //Iterators
                                geometryIndex+=2;
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