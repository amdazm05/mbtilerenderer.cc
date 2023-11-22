#include <mbtilecacher.hpp>
#include <iostream>

int main()
{
    mbtile::MbTileCacher cacher("./sample/islamabad.mbtiles");
    if(cacher.query_tile(14,11481,9827))
        std::cout<<"TEST PASSED";
    return {};
}