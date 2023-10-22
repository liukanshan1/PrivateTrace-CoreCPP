//
// Created by 12695 on 2023/3/18.
//

#ifndef C___ENCTMLOCDATA_H
#define C___ENCTMLOCDATA_H

#include <iostream>
#include "../Area/EncryptedCircle.hpp"
#include <ctime>

class ConcentricCircles;

class EncTmLocData {
private:
    EncryptedCircle eCircle;
    time_t date;
    EncTmLocData* pETLD = nullptr;
    EncTmLocData* nETLD = nullptr;
    ConcentricCircles* cCircles = nullptr;
public:
    EncTmLocData(Location loc, time_t date, double accuracy) {
        this->eCircle = EncryptedCircle(loc, accuracy);
        this->date = date;
    }

    EncTmLocData(EncryptedCircle eC, time_t date): eCircle(eC), date(date) {}

    EncryptedCircle getCircle() {
        return eCircle;
    }

    time_t getDate() {
        return date;
    }

    void setcCircles(ConcentricCircles* cCircles) {
        this->cCircles = cCircles;
    }
    ConcentricCircles *getCCircles() const {
        return cCircles;
    }

    void setNext(EncTmLocData* nETLD) {
        this->nETLD = nETLD;
    }

    void setPrevious(EncTmLocData* pETLD) {
        this->pETLD = pETLD;
    }

    bool hasNext() {
        return nETLD != nullptr;
    }

    EncTmLocData* next() {
        return nETLD;
    }

    bool hasPrevious() {
        return pETLD != nullptr;
    }

    EncTmLocData* previous() {
        return pETLD;
    }
};

#endif //C___ENCTMLOCDATA_H
