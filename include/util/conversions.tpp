#ifndef _CONVERSIONS
#define _CONVERSIONS

#include <cmath>
#include <iostream>
#include <numbers>
#define M_PI_CONV  3.14159265358979323846f
// References here
//https://wiki.openstreetmap.org/wiki/Slippy_map_tilenames#Lon..2Flat._to_tile_numbers_2
namespace utils
{
    template<typename T>
    inline std::pair<double,double> tile_to_latlong(int zoom, T x,T y)
    {
        double longi = y / (double)(1 << zoom) * 360.0 - 180;
        x = (1 << zoom) - x - 1;
        double nx = M_PI_CONV *(1 - 2.0* x / (double)(1 << zoom));
	    double lat = 180.0 / M_PI_CONV * atan(sinh(nx));
        return {lat,longi};
    }

    template<typename T>
    inline std::pair<int,int> latlong_to_tile(int zoom, T lat,T longi)
    {
        int ni = (1<<zoom);
        double n= (double)ni;
        lat   = lat * (M_PI_CONV/180);
        int x = ((longi +180)/(360))*n;
        int y = (int)(floor((1.0 - asinh(tan(lat)) / M_PI_CONV) / 2.0 * n));
        return {x,y};
    }

}

#endif //_CONVERSIONS