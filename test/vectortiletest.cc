#include <mbtilecacher.hpp>
#include <vectortilecodec.hpp>

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    mbtile::MbTileCacher cacher("./sample/islamabad.mbtiles");
    vector_tile::VectorTileCodec codec;
    try
    {
        {
            int zoom = 3;
            int column = 5 ;
            int row  = 4 ;
            bool queryres =cacher.query_tile(zoom,column,row);
            if(queryres)
            {
                std:: cout<<"QUERY PASSED"<<std::endl;
                mbtile::tile_t t;
                std::string s = (cacher.fetch_mb_tile(zoom,(std::size_t)column,(std::size_t)row).value_or(t).pbtile);
                codec.Decode(zoom,(std::size_t)column,(std::size_t)row,s);
            }   
            else
            {
                throw std::runtime_error("Error in querying");
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    google::protobuf::ShutdownProtobufLibrary();
    return {};
}