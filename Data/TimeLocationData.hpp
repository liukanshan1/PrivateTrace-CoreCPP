//
// Created by 12695 on 2023/3/18.
//

#ifndef C___TIMELOCATIONDATA_H
#define C___TIMELOCATIONDATA_H
#include <iostream>
#include "../Geo/Location.hpp"
#include <ctime>
#include "../Global.hpp"
#include "../Area/Circle.hpp"
#include "EncTmLocData.hpp"

using namespace std;

class TimeLocationData {
private:
    Location loc;
    tm date;
    double accuracy = Global::RADIUS;
    TimeLocationData* pTLD = nullptr;
    TimeLocationData* nTLD = nullptr;

public:
    TimeLocationData(Location loc, tm date) {
        this->loc = loc;
        this->date = date;
    }

    TimeLocationData(Location loc, tm date, TimeLocationData* nTLD) {
        this->loc = loc;
        this->date = date;
        this->nTLD = nTLD;
    }

    void setDate(tm date) {
        this->date = date;
    }

    void setNext(TimeLocationData* nTLD) {
        this->nTLD = nTLD;
    }

    void setPrevious(TimeLocationData* pTLD) {
        this->pTLD = pTLD;
    }


    Location getLoc() {
        return loc;
    }

    tm getDate() {
        return date;
    }

    double getAccuracy() {
        return accuracy;
    }

    bool hasNext() {
        return nTLD != nullptr;
    }

    TimeLocationData* next() {
        return nTLD;
    }

    bool hasPrevious() {
        return pTLD != nullptr;
    }

    TimeLocationData* previous() {
        return pTLD;
    }

    EncTmLocData* encrypt() {
        return new EncTmLocData(loc, mktime(&date), accuracy);
    }

    Circle getCircle() {
        return Circle(loc, accuracy);
    }
};

#endif //C___TIMELOCATIONDATA_H
