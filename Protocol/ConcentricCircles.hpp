//
// Created by 12695 on 2023/3/18.
//

#ifndef C___CONCENTRICCIRCLES_H
#define C___CONCENTRICCIRCLES_H

#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include "../Data/EncTmLocData.hpp"
#include <thread>
#include "Prune.h"

class CCircleTree;

class ConcentricCircles {
private:
    std::vector<EncTmLocData*> eTLDs;
    std::unordered_map<EncTmLocData *, int> eTLDsIndex;
    std::vector<EncSquareDistance*> distances;
    const int rootIndex = 0;
    EncTmLocData *rootETLD = nullptr;
public:
    ConcentricCircles(EncTmLocData *eTLD) {
        eTLDs.push_back(eTLD);
        rootETLD = eTLDs[rootIndex];
        for (int i = 0; i < eTLDs.size(); i++) {
            EncTmLocData *eTLD = eTLDs[i];
            eTLDsIndex[eTLD] = i;
            eTLD->setcCircles(this);
        }
    }

    void add(EncTmLocData *eTLD) {
        eTLD->setcCircles(this);
        eTLDs.push_back(eTLD);
        eTLDsIndex[eTLD] = eTLDs.size() - 1;
    }

    void init() {
        distances.clear();
        for (int i = 1; i < eTLDs.size(); i++) {
            auto t = new EncSquareDistance(rootETLD->getCircle().encSquareDistance(eTLDs[i]->getCircle()));
            t->index = i;
            distances.push_back(t);
        }
        std::sort(distances.begin(), distances.end(), edistcmp);
    }

    void prune(int i) {
        p.prune(this, i);
    }

    void unprune(int i) {
        p.unprune(this, i);
    }

    void getprune(int i) {
        p.getprune(this, i);
    }

    void prune(EncTmLocData *eTld) {
        prune(eTLDsIndex[eTld]);
    }

    void unprune(EncTmLocData *eTld) {
        unprune(eTLDsIndex[eTld]);
    }

    void getprune(EncTmLocData *eTld) {
        getprune(eTLDsIndex[eTld]);
    }

    int size() {
        return eTLDs.size();
    }

    bool compare(EncryptedCircle circle) {
        mpz_t squareDistance;
        mpz_init(squareDistance);
        int compare = rootETLD->getCircle().howFarAway(circle, squareDistance);
        if (compare == -1) {
            return false;
        } else if (compare == 0) {
            this->unprune(0);
            EncTmLocData *previous = eTLDs[rootIndex];
            EncTmLocData *next = previous;
            for (int j = 0; j < Global::PRUNE_NUM[Global::PRUNE_NUM_LENGTH - 1]; j++) {
                if (previous->hasPrevious()) {
                    previous = previous->previous();
                    previous->getCCircles()->unprune(previous);
                }
                if (next->hasNext()) {
                    next = next->next();
                    next->getCCircles()->unprune(next);
                }
            }
        } else if (compare > 0) {
            this->prune(0);
            EncTmLocData *previous = eTLDs[rootIndex];
            EncTmLocData *next = previous;
            for (int j = 0; j < compare; j++) {
                if (previous->hasPrevious()) {
                    previous = previous->previous();
                    previous->getCCircles()->prune(previous);
                }
                if (next->hasNext()) {
                    next = next->next();
                    next->getCCircles()->prune(next);
                }
            }
        }
        auto floorKey = distances.begin();
        auto ceilingKey = distances.end();
        if (distances.size() > 33) {
            EncSquareDistance floor(Global::RADIUS2);
            EncSquareDistance ceil(squareDistance, floor);
            floorKey = std::lower_bound(distances.begin(), distances.end(), &floor, edistcmp);
            ceilingKey = std::upper_bound(distances.begin(), distances.end(), &ceil, edistcmp);
        }
//        if (distances.size() > 33) {
//            EncSquareDistance ceil(squareDistance, Global::RADIUS2*2);
//            ceilingKey = std::upper_bound(distances.begin(), distances.end(), &ceil, edistcmp);
//        }
//        if (floorKey != distances.begin()) {
//            cout<<"PRUNE1"<<endl;
//        }
        // compare circle with subCircles
        while (floorKey != distances.end() && floorKey != ceilingKey) {
            int i = (*floorKey)->index;
            if (p.getPruned(this, i)) {
                //cout<<"PRUNE2"<<endl;
                this->getprune(i);
                EncTmLocData *previous = eTLDs[i];
                EncTmLocData *next = previous;
                for (int j = 0; j < Global::PRUNE_NUM[Global::PRUNE_NUM_LENGTH - 1]; j++) {
                    if (previous->hasPrevious()) {
                        previous = previous->previous();
                        previous->getCCircles()->getprune(previous);
                    }
                    if (next->hasNext()) {
                        next = next->next();
                        next->getCCircles()->getprune(next);
                    }
                }
                floorKey++;
                continue;
            }
            int compare = eTLDs[i]->getCircle().howFarAway(circle, squareDistance);
            if (compare == -1) {
                return false;
            } else if (compare == 0) {
                this->unprune(i);
                EncTmLocData *previous = eTLDs[i];
                EncTmLocData *next = previous;
                for (int j = 0; j < Global::PRUNE_NUM[Global::PRUNE_NUM_LENGTH - 1]; j++) {
                    if (previous->hasPrevious()) {
                        previous = previous->previous();
                        previous->getCCircles()->unprune(previous);
                    }
                    if (next->hasNext()) {
                        next = next->next();
                        next->getCCircles()->unprune(next);
                    }
                }
            } else if (compare > 0) {
                this->prune(i);
                EncTmLocData *previous = eTLDs[i];
                EncTmLocData *next = previous;
                for (int j = 0; j < compare; j++) {
                    if (previous->hasPrevious()) {
                        previous = previous->previous();
                        previous->getCCircles()->prune(previous);
                    }
                    if (next->hasNext()) {
                        next = next->next();
                        next->getCCircles()->prune(next);
                    }
                }
            }
            floorKey++;
        }
        return true;
    }
};

#endif //C___CONCENTRICCIRCLES_H
