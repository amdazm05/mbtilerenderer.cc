#ifndef _CONVERSIONS
#define _CONVERSIONS

#include <cmath>
#include <iostream>
#include <numbers>

// References here
//https://wiki.openstreetmap.org/wiki/Slippy_map_tilenames#Lon..2Flat._to_tile_numbers_2
namespace utils
{
    template<typename T>
    inline std::pair<T,T> tile_to_latlong(int zoom, T x,T y)
    {
        int ni = (1<<zoom);
        double n= (double)ni;
        double ng = std::numbers::pi - 2.0 * std::numbers::pi * y / (n);
        T longi   =  (x/n)*((T)360) -180;
        T lat = 180.0 / std::numbers::pi * atan(0.5 * (exp(ng) - exp(-ng)));
        return {lat,longi};
    }

    template<typename T>
    inline std::pair<int,int> latlong_to_tile(int zoom, T lat,T longi)
    {
        int ni = (1<<zoom);
        double n= (double)ni;
        lat   = lat * (std::numbers::pi/180);
        int x = ((longi +180)/(360))*n;
        int y = (int)(floor((1.0 - asinh(tan(lat)) / std::numbers::pi) / 2.0 * n));
        return {x,y};
    }

}

#endif //_CONVERSIONS