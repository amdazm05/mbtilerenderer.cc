#include <mbtilecacher.hpp>
#include <vectortilecodec.hpp>

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    mbtile::MbTileCacher cacher("./sample/islamabad.mbtiles");
    vector_tile::VectorTileCodec codec;
    if(cacher.query_tile(14,11481,9827))
    {
        std:: cout<<"QUERY PASSED";
        mbtile::tile_t t;
        std::string s = (cacher.fetch_mb_tile(14,(std::size_t)11481,(std::size_t)9827).value_or(t).pbtile);
        codec.Decode(14,(std::size_t)11481,(std::size_t)9827,s);
    }   
    else
    {
        throw std::runtime_error("Error in querying");
    }
    google::protobuf::ShutdownProtobufLibrary();
    return {};
}