#include <SQLiteCpp/SQLiteCpp.h>
#include <mbtile/mbtile.hpp>
#include <fstream>
#include <util/compressdecompressor.hpp>

int main()
{
    std::string path = "./sample/countries-raster.mbtiles";
    std::string query = "SELECT tile_data FROM tiles WHERE zoom_level = 1 AND  tile_column = 0 AND tile_row = 1;";
    try
    {
        SQLite::Database db(path);
        SQLite::Statement statement(db,query);
        bool dbExists  = db.tableExists("tiles");
        while (statement.executeStep())
        {
            std::string s = statement.getColumnName(0);
            char * data = nullptr;
            data = (char *)statement.getColumn(0).getBlob();
            int len = statement.getColumn(0).getBytes();
            std::stringstream st;
            st<<"tile.png";
            std::fstream file(st.str(),std::ios::binary| std::ios::trunc|std::ios::in|std::ios::out);
            file.write((char *)data,len);
            file.flush();
            file.close();
            std::cout<<" TEST PASSED"<<std::endl;
        }

    }
    catch(std::exception &e)
    {

    }
    return {};
}