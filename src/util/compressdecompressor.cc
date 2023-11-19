#include <util/compressdecompressor.hpp>

namespace utils
{
    std::optional<std::string> ComDecompressor::decompress(std::weak_ptr<char> compressed_pointer 
        ,std::size_t datalen)
    {
        std::shared_ptr<char> compressed_pointer_ = compressed_pointer.lock();
        if(isCompressed(compressed_pointer_,datalen))
        {
            std::string decompressed_data = gzip::decompress(
                compressed_pointer_.get()
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
    bool ComDecompressor::isCompressed(std::shared_ptr<char> data,std::size_t datalen)
    {
        return gzip::is_compressed(
            data.get()
            ,datalen);
    }
}