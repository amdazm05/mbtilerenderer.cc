#include <geometry/geometryparams.hpp>

int main()
{

    geometry::vertice_vector_2D<int> closedpathCW=
    {{
        {0,0},
        {-1,1},
        {-2,2},
        {-1,3},
        {0,0}
    }};
    geometry::Winding winding = geometry::CheckWindingOrderAVX(closedpathCW);
    geometry::vertice_vector_2D<int> closedpathCCW=
    {{
        {0,0},
        {-1,1},
        {-2,2},
        {-1,3},
        {0,0}
    }};
    winding = geometry::CheckWindingOrderAVX(closedpathCCW);
    
    return 0;
}