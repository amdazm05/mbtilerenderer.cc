#include <mbtilecacher.hpp>
#include <iostream>

int main()
{
    mbtile::MbTileCacher cacher("./sample/countries-raster.mbtiles");
    cacher.query_tile(1,0,1);
    return {};
}