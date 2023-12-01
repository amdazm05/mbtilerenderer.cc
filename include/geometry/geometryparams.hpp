#ifndef _GEOMETRY_PARAMS
#define _GEOMETRY_PARAMS

#include <immintrin.h>
#include <type_traits>
#include <cstdint>
#include <vector>
#include <stdexcept>

#define COORDINATES(x,y) _mm_set_ps(0,0,y,x)
#define x first
#define y second

namespace geometry
{
    template<typename T>
    using vertice_2D = std::pair<T, T>;
    template<typename T>
    using vertice_vector_2D = std::vector<vertice_2D<T>>;
    ///@brief An exterior ring is DEFINED as a linear ring having a positive area as calculated by applying the surveyor's formula
    // An exterior ring is DEFINED as a linear ring having a positive area as calculated by applying the surveyor's formula
    template<typename T>
    using polygon_2D_dual_rings = std::pair<vertice_vector_2D<T>,
        std::vector<vertice_vector_2D<T>>>;

    enum class Winding : uint32_t
    {
        COUNTER_CLOCK_WISE    = 1,
        CLOCK_WISE            = 2,
    };

    // Winding algo -->  O(n)
    // https://docs.mapbox.com/data/tilesets/guides/vector-tiles-standards/
    // https://www.cuemath.com/geometry/cross-product/
                       
    inline float cross_product_2D_AVX(__m128 &origin,__m128 &a,__m128 &b)
    {
        float resf[4];
        b = _mm_sub_ps(b,origin);
        b = _mm_shuffle_ps(b,b,_MM_SHUFFLE(2,3,0,1));
        _mm_storeu_ps(resf,_mm_mul_ps(_mm_sub_ps(a,origin),b));
        return resf[0]-resf[1];
    }    
    inline float cross_product_2D(std::pair<float,float> origin,std::pair<float,float> &a,std::pair<float,float> &b)
    {
        a.x = a.x-origin.x;
        a.y = a.y-origin.y;
        b.x = b.x-origin.x;
        b.y = b.y-origin.y;
        return (a.x*b.y) - (a.y*b.x);
    }     
    template<typename T>
    Winding CheckWindingOrderAVX(std::vector<geometry::vertice_2D<T>> & points)
    {
        std::size_t n = points.size();
        if(n<2) throw std::runtime_error("Winding Order: Cannot compute winding order, there must be atleast 2 points");
        __m128 origin  = COORDINATES(points[0].x,points[0].y);
        double winding = 0;
        for(std::size_t i=0;i<n;i++)
        {
            std::size_t nextIndex = (i+1)%n;
            __m128 currPoint  = COORDINATES(points[i].x,points[i].y);
            __m128 nextPoint  = COORDINATES(points[nextIndex].x,points[nextIndex].y);
            winding += cross_product_2D_AVX(origin,currPoint,nextPoint);
        }
        return winding<0?Winding::CLOCK_WISE:Winding::COUNTER_CLOCK_WISE;
    }

    template<typename T>
    Winding CheckWindingOrder(std::vector<geometry::vertice_2D<T>> & points)
    {
        std::size_t n = points.size();
        if(n<2) throw std::runtime_error("Winding Order: Cannot compute winding order, there must be atleast 2 points");
        std::pair<float,float> origin=points[0];
        double winding = 0;
        #pragma unroll
        for(std::size_t i=0;i<n;i++)
        {
            std::size_t nextIndex = (i+1)%n;
            std::pair<float,float> currPoint  = points[i];
            std::pair<float,float> nextPoint  = points[nextIndex];
            winding += cross_product_2D(origin,currPoint,nextPoint);
        }
        return winding<0?Winding::CLOCK_WISE:Winding::COUNTER_CLOCK_WISE;
    }
}

#endif //_GEOMETRY_PARAMS