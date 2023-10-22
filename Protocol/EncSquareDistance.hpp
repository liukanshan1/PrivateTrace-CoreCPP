//
// Created by 12695 on 2023/3/18.
//

#ifndef C___ENCSQUAREDISTANCE_H
#define C___ENCSQUAREDISTANCE_H
#include "gmp.h"
#include "../Global.hpp"

class EncSquareDistance {
private:
    mpz_t squareDistance;
public:
    int index;
    EncSquareDistance(EncryptedPoint p1, EncryptedPoint p2) {
        mpz_init(squareDistance);
        p1.squareDistance(squareDistance, p2);
    }

    EncSquareDistance(double t) {
        mpz_init(this->squareDistance);
        encryptDouble(t, squareDistance);
    }

    EncSquareDistance(mpz_t t, EncSquareDistance& floor) {
        mpz_init(this->squareDistance);
        Global::pai.scl_mul(squareDistance, t, 2);
        Global::pai.add(this->squareDistance, floor.squareDistance, this->squareDistance);
    }

    EncSquareDistance(mpz_t d2, double r2) {
        mpz_init(this->squareDistance);
        Global::pai.scl_mul(squareDistance, d2, 2);
        mpz_t tmp;
        mpz_init(tmp);
        encryptDouble(r2, tmp);
        Global::pai.add(this->squareDistance, this->squareDistance, tmp);
    }

    bool operator<(EncSquareDistance& o) {
        return Global::scmp(this->squareDistance, o.squareDistance) == 1;
    }

    double getSquareDistance() {
        mpz_t tmp;
        mpz_init(tmp);
        Global::pai.decrypt(tmp, squareDistance);
        return mpz_get_d(tmp);
    }
};

bool edistcmp(EncSquareDistance* a, EncSquareDistance* b) {
    return *a < *b;
}

#endif //C___ENCSQUAREDISTANCE_H
