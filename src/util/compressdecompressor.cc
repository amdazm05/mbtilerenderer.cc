#include <util/compressdecompressor.hpp>

namespace utils
{
    std::optional<std::string> ComDecompressor::decompress(char * compressed_pointer 
        ,std::size_t datalen)
    {
        if(isCompressed(compressed_pointer,datalen))
        {
            std::string decompressed_data = gzip::decompress(
                compressed_pointer
                ,datalen);
            return decompressed_data;
        }
        return std::nullopt;
    }
    std::optional<std::string> ComDecompressor::compress(std::string & s)
    {
        std::string res;
        try
        {
            res = gzip::compress(reinterpret_cast<const char *>(s.data()),s.length());
        }
        catch(const std::exception& e)
        {
            return std::nullopt;
        }
        return res;
    }
    bool ComDecompressor::isCompressed(char * data,std::size_t datalen)
    {
        return gzip::is_compressed(
            data
            ,datalen);
    }
}