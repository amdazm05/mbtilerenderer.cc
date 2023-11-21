#include <mbtilecacher.hpp>

namespace mbtile
{
    MbTileCacher::MbTileCacher(std::string && path): db(path)
    {

    }

    MbTileCacher::~MbTileCacher()
    {

    }
    bool MbTileCacher::query_tile(std::size_t zoomlevel,std::size_t x,std::size_t y)
    {
        std::string query = "SELECT tile_data FROM tiles WHERE zoom_level ="+ 
                std::to_string(zoomlevel) + "AND  tile_column =" 
                +std::to_string(x)+ "AND tile_row ="
                +std::to_string(1)+";";
        try
        {
            SQLite::Statement statment(this->db,std::move(query));
            mbtile::tile_t tile;
            while(statment.executeStep())
            {
                statment.getColumn(0).getBlob();
            }
        }
        catch(std::exception & e)
        {
            std::cerr<<e.what()<<std::endl;
        }
        return {};
    }
}

