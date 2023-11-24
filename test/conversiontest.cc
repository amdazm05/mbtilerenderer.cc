#include <util/conversions.tpp>
#include <vector_tile.pb.h>
int main()
{
    auto answer = utils::tile_to_latlong<double>(1,0,1);
    auto reverse = utils::latlong_to_tile<double>(1,answer.first,answer.second);
    auto answer1 = utils::tile_to_latlong<double>(14,9791,11481);
    auto reverse2 = utils::latlong_to_tile<double>(14,answer1.first,answer1.second);
    return {};
}