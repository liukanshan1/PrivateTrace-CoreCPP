//
// Created by 12695 on 2023/3/17.
//

#ifndef PriCT_LOCATION_HPP
#define PriCT_LOCATION_HPP

#include "cmath"
#include "../Utils/Tuple.hpp"
#include "../Utils/Pair.hpp"
#include "../Area/EncryptedPoint.hpp"
#include "Geo.hpp"

Tuple<double, double, double> gcj02ToXYZ(double lng, double lat, double high);

class Location {

private:
    double latitude;
    double longitude;
    double altitude = 0.0;

public:

    Location() {}

    Location(double latitude, double longitude, double altitude) {
        this->latitude = latitude;
        this->longitude = longitude;
        this->altitude = altitude;
    }

    Location(double latitude, double longitude) {
        this->latitude = latitude;
        this->longitude = longitude;
    }

    double getLatitude() {
        return latitude;
    }

    double getLongitude() {
        return longitude;
    }

    Tuple<double, double, double> toXYZ() {
        return gcj02ToXYZ(longitude, latitude, altitude);
    }

    EncryptedPoint encrypt() {
        Tuple<double, double, double> xyz = toXYZ();
        return EncryptedPoint(xyz.first, xyz.second, xyz.third);
    }

    double squareDistance(Location other) {
        return std::pow(distance(other), 2);
    }

    double distance(const Location& other) {
        return realDistance(latitude, longitude, other.latitude, other.longitude);
    }

    double encodeDistance(Location other) {
        Tuple<double, double, double> xyz1 = toXYZ();
        Tuple<double, double, double> xyz2 = other.toXYZ();
        double squareDist = std::pow(xyz1.first - xyz2.first, 2) + std::pow(xyz1.second - xyz2.second, 2) +
                            std::pow(xyz1.third - xyz2.third, 2);
        return std::sqrt(squareDist);
    }
};


const double X_PI = M_PI * 3000.0 / 180.0;
const double PI = M_PI;
const double A = 6378245.0;
const double EE = 0.00669342162296594323;
const int REDUCE[] = {2170000, -4380000, -4060000};

Tuple<double, double, double> gcj02ToXYZ(double lng, double lat, double high) {
    double n = 6378137.0 / std::sqrt(1 - EE * std::pow(std::sin(lat * PI / 180.0), 2));
    double x = (n + high) * std::cos(lat * PI / 180.0) * std::cos(lng * PI / 180.0) + REDUCE[0];
    double y = (n + high) * std::cos(lat * PI / 180.0) * std::sin(lng * PI / 180.0) + REDUCE[1];
    double z = (n * (1 - EE) + high) * std::sin(lat * PI / 180.0) + REDUCE[2];
    return Tuple<double, double, double>(x, y, z);
}

Tuple<double, double, double> gcj02ToXYZ(double lng, double lat) {
    return gcj02ToXYZ(lng, lat, 0);
}

#endif //PriCT_LOCATION_HPP
