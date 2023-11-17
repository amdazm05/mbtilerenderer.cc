#include <util/compressdecompressor.hpp>
int main()
{
    try
    {
        utils::ComDecompressor ComDecomObj;
        std::string teststring  = "This is a Test compression";

    }
    catch(std::exception & e)
    {
        std::cout<<"TEST FAILED"<<std::endl;
        std::cerr<<e.what()<<std::endl;
    }
    return {};
}