//
// Created by 12695 on 2023/3/17.
//

#ifndef PriCT_CIRCLE_HPP
#define PriCT_CIRCLE_HPP
#include <iostream>
#include <cmath>
#include "Point.hpp"
#include "EncryptedCircle.hpp"
#include <vector>

class Circle {
public:
    Point center;
    double radius;

    Circle(Point center, double radius) : center(center), radius(radius) {}

    double getRadius() {
        return radius;
    }

    Point getCenter() {
        return center;
    }

    EncryptedCircle encrypt() {
        return EncryptedCircle(center, radius);
    }

    bool isIntersect(std::vector<Circle> circles) {
        for (auto& circle : circles) {
            if (center.distance(circle.getCenter()) < radius + circle.getRadius()) {
                return true;
            }
        }
        return false;
    }

    bool isIntersect(Circle circle) {
        if (center.distance(circle.getCenter()) < radius + circle.getRadius()) {
            return true;
        }
        return false;
    }

};
#endif //PriCT_CIRCLE_HPP
