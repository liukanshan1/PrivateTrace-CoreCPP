//
// Created by lks on 23-3-18.
//

#ifndef PRICT_GEO_HPP
#define PRICT_GEO_HPP

#include<iostream>
#include "math.h"

using namespace std;
#define pi 3.1415926535897932384626433832795
#define EARTH_RADIUS 6378.137 //地球半径 KM

double rad(double d) {
    return d * pi / 180.0;
}

double realDistance(double lat1, double lng1, double lat2, double lng2)//lat1第一个点纬度,lng1第一个点经度,lat2第二个点纬度,lng2第二个点经度
{

    double a;
    double b;
    double radLat1 = rad(lat1);
    double radLat2 = rad(lat2);
    a = radLat1 - radLat2;
    b = rad(lng1) - rad(lng2);
    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
    s = s * EARTH_RADIUS;
    s = s * 1000;
    return s;
}

#endif //PRICT_GEO_HPP
