#include <util/compressdecompressor.hpp>
#include <memory>
#include <string>


int main()
{
    utils::ComDecompressor ComDecomObj;
    std::string teststring  = "This is a Test compression";
    std::string compressedString = ComDecomObj.compress(teststring).value_or("");
    std::shared_ptr<uint8_t> data = 
        std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(compressedString.data())); 
    std::string res = ComDecomObj.decompress(data,compressedString.length()).value_or("");
    if(res=="")
        throw std::runtime_error("FAILED");
    std::cout<<"TEST PASSED"<<std::endl;
    return 0;
}