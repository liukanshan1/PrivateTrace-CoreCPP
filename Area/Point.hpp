//
// Created by 12695 on 2023/3/17.
//

#ifndef PriCT_POINT_HPP
#define PriCT_POINT_HPP


#include <cmath>
#include "../Geo/Location.hpp"
#include "../Utils/Tuple.hpp"
#include "EncryptedPoint.hpp"

class Point {
public:
    double x, y, z;

    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point(Location loc) {
        Tuple<double, double, double> xyz = loc.toXYZ();
        this->x = xyz.first;
        this->y = xyz.second;
        this->z = xyz.third;
    }

    double distance(Point p) {
        return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2) + std::pow(p.z - z, 2));
    }

    EncryptedPoint encrypt() {
        return EncryptedPoint(x, y, z);
    }

    static double distance(Point p1, Point p2) {
        return p1.distance(p2);
    }
};



#endif //PriCT_POINT_HPP
