#ifndef _VECTOR_TILE
#define _VECTOR_TILE
#include <memory>
#include <string>
#include <vector_tile.pb.h>
#include <util/conversions.tpp>
#include <geometry./geometryparams.hpp>
/// @brief  Scope
///       - 

namespace vector_tile
{
    enum class CommandIntegers : uint32_t
    {
        NONE       = 0,
        MOVE_TO    = 1,
        LINE_TO    = 2,
        CLOSE_PATH = 7
    };
    class VectorTileCodec:std::enable_shared_from_this<VectorTileCodec>
    {
        private: 
            //min , max 
            std::pair<double,double> maxlonglatextents_;
            std::pair<double,double> minlonglatextents_;
            // difflat difflong
            std::pair<double,double> diffboundslatlong_;
            std::vector<geometry::vertice_2D<double>> points_;
            std::vector<geometry::vertice_2D<int>> points_tilecoords_;
            std::vector<geometry::vertice_vector_2D<double>> lines_;
            std::vector<geometry::polygon_2D_dual_rings<double>> polygons_;
            geometry::polygon_2D_dual_rings<double> currpolygons_;
        public:
            VectorTileCodec();
            ~VectorTileCodec();
            vector_tile::Tile_Feature Decode(std::size_t zoom,
                std::size_t column,std::size_t row ,std::string & s);
            // Not in V0.0 Scope right now
            ///@brief Future work 
            // void Encode()
    };
}

#endif //_VECTOR_TILE