//
// Created by 12695 on 2023/3/18.
//

#ifndef PriCT_ENCRYPTEDCIRCLE_HPP
#define PriCT_ENCRYPTEDCIRCLE_HPP

#include "EncryptedPoint.hpp"
#include "Circle.hpp"
#include "gmp.h"
#include "../Protocol/EncSquareDistance.hpp"
#include "../Global.hpp"

class EncryptedCircle {

private:

    EncryptedPoint encryptedPoint;
    double radius;

public:

    EncryptedCircle(){}

    EncryptedCircle(Point center, double radius) {
        this->encryptedPoint = EncryptedPoint(center.x, center.y, center.z);
        this->radius = radius;
    }

    EncryptedCircle(EncryptedPoint encryptedPoint, double radius) {
        this->encryptedPoint = encryptedPoint;
        this->radius = radius;
    }

    double getRadius() {
        return radius;
    }

    EncryptedPoint getEncryptedPoint() {
        return encryptedPoint;
    }

    void squareDistance(mpz_t res, EncryptedCircle other) {
        return encryptedPoint.squareDistance(res, other.encryptedPoint);
    }

    EncSquareDistance encSquareDistance(EncryptedCircle other) {
        return EncSquareDistance(encryptedPoint, other.encryptedPoint);
    }

    int isIntersect(double maxSquareDistance, mpz_t squareDistance) {
        mpz_t maxSquareDistanceEnc;
        mpz_init(maxSquareDistanceEnc);
        encryptDouble(maxSquareDistance, maxSquareDistanceEnc);
        return Global::scmp(squareDistance, maxSquareDistanceEnc);
    }

    /**
     * -1 相交
     * 0 不允许 prune
     * n 允许 prune 2n+1 个节点
     */
    int howFarAway(EncryptedCircle other, mpz_t squareDistance) {
        double maxSquareDistance = (radius + other.radius) * (radius + other.radius);
        this->squareDistance(squareDistance, other);
        int result = isIntersect(maxSquareDistance, squareDistance);
        if (result == 0) {
            //return 0;
            for (int i = 0; i < Global::COMPARE_DISTANCE_LENGTH; i++) {
                result = isIntersect(Global::COMPARE_DISTANCE[i], squareDistance);
                if (result != 0) {
                    //cout<< "修剪" << Global::PRUNE_NUM[i] << endl;
                    return Global::PRUNE_NUM[i];
                }
            }
            //cout<< "修剪" << Global::PRUNE_NUM[Global::PRUNE_NUM_LENGTH - 1] << endl;
            return Global::PRUNE_NUM[Global::PRUNE_NUM_LENGTH - 1];
        } else {
            return -1;
        }
    }

    bool isIntersect(EncryptedCircle other) {
        double maxSquareDistance = (radius + other.radius) * (radius + other.radius);
        mpz_t maxSquareDistanceEnc, squareDistance;
        mpz_inits(maxSquareDistanceEnc, squareDistance, NULL);
        encryptDouble(maxSquareDistance, maxSquareDistanceEnc);
        this->squareDistance(squareDistance, other);
        return Global::scmp(squareDistance, maxSquareDistanceEnc);
    }
};

#endif //PriCT_ENCRYPTEDCIRCLE_HPP
