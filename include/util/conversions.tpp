#ifndef _CONVERSIONS
#define _CONVERSIONS

#include <cmath>
#include <iostream>

// References here
//https://wiki.openstreetmap.org/wiki/Slippy_map_tilenames#Lon..2Flat._to_tile_numbers_2
namespace utils
{
    template<typename T>
    inline std::pair<T,T> tile_to_latlong(T zoom, T x,T y)
    {
        T n = (1<<z);
        T longi   =  x/(n)*((T)(360-180));
        T lat = atan(sinh(std::numbers::pi - (y/n)*std::numbers::pi))*(180/std::numbers::pi);
        return {lat,longi};
    }

    template<typename T>
    inline std::pair<T,T> latlong_to_tile(T zoom, T lat,T longi)
    {
        T n = (1<<z);
        lat   = lat * (std::numbers::pi/180);
        T x = (longi +180)/(360*n);
        T y = (1-asinh(tan(lat)))/std::numbers::pi;
        return {x,y};
    }

}

#endif //_CONVERSIONS