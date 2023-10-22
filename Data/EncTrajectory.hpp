//
// Created by 12695 on 2023/3/18.
//

#ifndef C___ENCTRAJECTORY_H
#define C___ENCTRAJECTORY_H

#include <iostream>
#include <vector>
#include "TimeLocationData.hpp"

class EncTrajectory {
private:
    std::vector<EncTmLocData*> eTLDs;
    std::string name;
public:
    EncTrajectory(std::vector<TimeLocationData*> tlds, std::string name){
        EncTmLocData* pETLD = nullptr;
        for (auto& tld : tlds) {
            EncTmLocData* cETLD = tld->encrypt();
            if (pETLD != nullptr) {
                pETLD->setNext(cETLD);
            }
            cETLD->setPrevious(pETLD);
            eTLDs.push_back(cETLD);
            pETLD = cETLD;
        }
        this->name = name;
    }

    std::string getName() const {
        return name;
    }

    std::vector<EncTmLocData*> getETLDs() const {
        return eTLDs;
    }
};

#endif //C___ENCTRAJECTORY_H
