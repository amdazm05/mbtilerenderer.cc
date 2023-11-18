#include <util/compressdecompressor.hpp>

namespace utils
{
    std::optional<std::string> ComDecompressor::decompress(std::shared_ptr<uint8_t> compressed_pointer 
        ,std::size_t datalen)
    {
        if(isCompressed(compressed_pointer,datalen))
        {
            std::string decompressed_data = gzip::decompress(
                reinterpret_cast<const char *>(compressed_pointer.get())
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
        return std::move(res);
    }
    bool ComDecompressor::isCompressed(std::shared_ptr<uint8_t> data,std::size_t datalen)
    {
        return gzip::is_compressed(
            reinterpret_cast<const char *>(data.get())
            ,datalen);
    }
}