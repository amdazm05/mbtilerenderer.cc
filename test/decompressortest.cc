#include <util/compressdecompressor.hpp>
#include <memory>
#include <string>


int main()
{
    utils::ComDecompressor ComDecomObj;
    std::string teststring  = "This is a Test compression";
    std::string compressedString = ComDecomObj.compress(teststring).value_or("");
    std::string res = ComDecomObj.decompress(
        compressedString.data(),
        compressedString.length()).value_or("");
    if(res=="This is a Test compression")
        std::cout<<"TEST PASSED"<<std::endl;
    else throw std::runtime_error("FAILED");
    return 0;
}