#ifndef _GEOMETRY_PARAMS
#define _GEOMETRY_PARAMS

namespace geometry
{
    template<typename T>
    using vertice_2D = std::pair<T, T>;
    template<typename T>
    using vertice_vector_2D = std::vector<vertice_2D<T>>;
    ///@brief An exterior ring is DEFINED as a linear ring having a positive area as calculated by applying the surveyor's formula
    // An exterior ring is DEFINED as a linear ring having a positive area as calculated by applying the surveyor's formula
    template<typename T>
    using polygon_2D_dual_rings = std::pair<std::vector<vertice_vector_2D<T>>,
        std::vector<vertice_vector_2D<T>>>;

    enum class Winding : uint32_t
    {
        COUNTER_CLOCK_WISE    = 1,
        CLOCK_WISE            = 2,
    };

    // Winding algo -->  O(n)
    // https://docs.mapbox.com/data/tilesets/guides/vector-tiles-standards/
    // https://www.cuemath.com/geometry/cross-product/
    template<typename T>
    Winding CheckWindingOrder(geometry::vertice_vector_2D<T> & points)
    {
        //Accumulate cross products
        // if cummulative +ve then proceed as cclock
        // if cummulative -ve then proceed as clock
    }                       
}

#endif //_GEOMETRY_PARAMS