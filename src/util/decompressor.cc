#include <util/decompressor.hpp>

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
            return std::move(decompressed_data);
        }
        return std::nullopt;
    }
    inline bool isCompressed(std::shared_ptr<uint8_t> data,std::size_t datalen)
    {
        return gzip::is_compressed(
            reinterpret_cast<const char *>(data.get())
            ,datalen);
    }
}