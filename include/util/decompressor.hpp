#ifndef _DECOMPRESSOR
#define _DECOMPRESSOR
#include <string>
#include <optional>
#include <memory>
#include <iostream>

#include <gzip/decompress.hpp>
#include <gzip/compress.hpp>
#include <gzip/utils.hpp>

namespace utils
{
    class ComDecompressor
    {
        public:
            //Constructors
            ComDecompressor()=default;
            ~ComDecompressor()=default;
        public:
            std::optional<std::string> 
                decompress(std::shared_ptr<uint8_t> compressed_pointer ,std::size_t datalen);
        private:
            bool isCompressed(std::shared_ptr<uint8_t> data,std::size_t datalen);
    };
}

#endif //_DECOMPRESSOR