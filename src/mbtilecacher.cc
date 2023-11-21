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
        try
        {
            SQLite::Statement statment(this->db_,std::move(query));
            mbtile::tile_t tile;
            while(statment.executeStep())
            {
                std::shared_ptr<char> compressed_blob((char *)statment.getColumn(0).getBlob());
                std::size_t datalen = statment.getColumn(0).getBytes();
                tile.pbtile = std::shared_ptr<char>(
                    comdecomObj_.decompress(std::weak_ptr<char>(compressed_blob),datalen).value().data());
            }
        }
        catch(std::exception & e)
        {
            std::cerr<<e.what()<<std::endl;
        }
        return {};
    }
}

