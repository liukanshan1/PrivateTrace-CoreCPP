//
// Created by 12695 on 2023/3/18.
//

#ifndef C___TRAJECTORY_H
#define C___TRAJECTORY_H

#include <iostream>
#include <vector>
#include "TimeLocationData.hpp"
#include <map>
#include "../Area/Circle.hpp"
#include "EncTrajectory.hpp"

class Trajectory {
private:
    std::vector<TimeLocationData*> TLDs;
    std::string name;

public:
    Trajectory(std::vector<TimeLocationData*> tlds, std::string name) : TLDs(tlds), name(name) {}

    std::string getName() const {
        return name;
    }

    std::vector<TimeLocationData*> getTLDs() const {
        return TLDs;
    }

    EncTrajectory encrypt() const {
        return EncTrajectory(TLDs, name);
    }

    static bool isIntersect(const Trajectory& t1, const Trajectory& t2) {
        // 判断时间重合
        std::map<time_t, std::vector<Circle>> positiveCircles;
        for (auto& tld : t1.getTLDs()) {
            tm startDate = tld->getDate();
            std::vector<Circle> circles = positiveCircles[mktime(&startDate)];
            circles.push_back(tld->getCircle());
            positiveCircles[mktime(&startDate)] = circles;
        }
        for (auto& tld : t2.getTLDs()) {
            tm startDate = tld->getDate();
            auto circlesIt = positiveCircles.find(mktime(&startDate));
            if (circlesIt == positiveCircles.end()) {
                continue;
            }
            std::vector<Circle> circles = circlesIt->second;
            if (tld->getCircle().isIntersect(circles)) {
                return true;
            }
        }
        return false;
    }

};

#endif //C___TRAJECTORY_H
