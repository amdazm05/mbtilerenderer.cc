#ifndef _GEOMETRY_PARAMS
#define _GEOMETRY_PARAMS

namespace geometry
{
    template<typename T> 
    typedef typename  std::pair<T,T> vertice_2D<T>;
    template<typename T> 
    typedef typename  std::vector<vertice_2D<T>> vertice_vector_2D<T>;     
    ///@brief An exterior ring is DEFINED as a linear ring having a positive area as calculated by applying the surveyor's formula
    // An exterior ring is DEFINED as a linear ring having a positive area as calculated by applying the surveyor's formula
    // template<typename T> 
    // typedef typename  std::pair<vertice_vector_2D<T>,vertice_vector_2D<T>> polygon_2D_dual<T>;                            
}

#endif //_GEOMETRY_PARAMS