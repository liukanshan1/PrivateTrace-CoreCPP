//
// Created by 12695 on 2023/3/18.
//

#ifndef C___CCIRCLETREE_H
#define C___CCIRCLETREE_H

#include <thread>
#include <map>
#include <unordered_map>
#include "ConcentricCircles.hpp"
#include <vector>
#include "../Data/EncTrajectory.hpp"
#include <pthread.h>

class CCircleTree {
public:
    std::map<time_t, ConcentricCircles *> ccTree;

    void add(EncTrajectory &eTrajectory) {
        std::vector<EncTmLocData *> eTLDs = eTrajectory.getETLDs();
        for (int i = 0; i < eTLDs.size(); i++) {
            EncTmLocData *eTLD = eTLDs[i];
            auto startDate = eTLD->getDate();
            auto ccs = ccTree.find(startDate);
            if (ccs == ccTree.end()) {
                ccTree.insert(pair<time_t, ConcentricCircles *>(startDate, new ConcentricCircles(eTLD)));
            } else {
                ccs->second->add(eTLD);
            }
        }
    }

    void init() {
        for (auto ccs: ccTree) {
            ccs.second->init();
        }
    }

    bool compare(EncTrajectory eTrajectory) {
        p.refresh();
        std::vector<EncTmLocData *> eTLDs = eTrajectory.getETLDs();
        for (int i = 0; i < eTLDs.size(); i++) {
            EncTmLocData *eTLD = eTLDs[i];
            auto ccs = ccTree.find(eTLD->getDate());
            if (ccs == ccTree.end()) {
                continue;
            }
            if (!ccs->second->compare(eTLD->getCircle())) {
                return false;
            }
        }
        return true;
    }

};

#endif //C___CCIRCLETREE_H
