#include <mbtilecacher.hpp>

namespace mbtile
{
    MbTileCacher::MbTileCacher(std::string && path): db_(path)
    {

    }

    MbTileCacher::~MbTileCacher()
    {

    }
    bool MbTileCacher::query_tile(std::size_t zoomlevel,std::size_t row,std::size_t column)
    {
        std::string query = "SELECT tile_data FROM tiles WHERE zoom_level ="+ 
                std::to_string(zoomlevel) + " AND  tile_column =" 
                +std::to_string(row)+ " AND tile_row ="
                +std::to_string(column)+";";
        bool check = false;
        try
        {
            SQLite::Statement statment(this->db_,std::move(query));
            mbtile::tile_t tile;
            while(statment.executeStep())
            {
                std::size_t datalen = statment.getColumn(0).getBytes();
                std::string result =
                    comdecomObj_.decompress((char *)statment.getColumn(0).getBlob(),datalen).value_or("");
                tile.tile_col = column;
                tile.tile_row = row;
                tile.pbtile = std::move(result);
                //Caches the tiles
                lrucache_.add(std::to_string(zoomlevel)+"/"+
                    std::to_string(row)+"/"+
                    std::to_string(column),std::move(tile));
                check = true;
            }
        }
        catch(std::exception & e)
        {
            std::cerr<<e.what()<<std::endl;
        }
        return check;
    }

    std::optional<mbtile::tile_t> MbTileCacher::fetch_mb_tile(std::size_t zoomlevel, std::size_t x,std::size_t y)
    {
        return lrucache_.get(std::to_string(zoomlevel)+"/"+
                    std::to_string(x)+"/"+
                    std::to_string(y));
    }
}

