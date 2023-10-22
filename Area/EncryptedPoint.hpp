//
// Created by 12695 on 2023/3/17.
//

#ifndef PriCT_ENCRYPTEDPOINT_HPP
#define PriCT_ENCRYPTEDPOINT_HPP

#include "../Utils/Utils.hpp"
#include "gmp.h"

class EncryptedPoint {
public:
    mpz_t encX4, encY4, encZ4, encXX, encYY, encZZ;
    mpz_t n2x,n2y,n2z;

    void encrypt1(double x, double y, double z) {
        mpz_inits(encX4, encY4, encZ4, encXX, encYY, encZZ, n2x, n2y, n2z, NULL);
        encryptDouble(x, encX4, FIXED_POINT/2);
        encryptDouble(y, encY4, FIXED_POINT/2);
        encryptDouble(z, encZ4, FIXED_POINT/2);
        encryptDouble(x * x, encXX);
        encryptDouble(y * y, encYY);
        encryptDouble(z * z, encZZ);
        encryptDouble(-2 * x, n2x, FIXED_POINT/2);
        encryptDouble(-2 * y, n2y, FIXED_POINT/2);
        encryptDouble(-2 * z, n2z, FIXED_POINT/2);
    }

    void encrypt2(double x, double y, double z) {
        mpz_inits(encX4, encY4, encZ4, encXX, encYY, encZZ, NULL);
        encryptDouble(x, encX4, FIXED_POINT/2);
        encryptDouble(y, encY4, FIXED_POINT/2);
        encryptDouble(z, encZ4, FIXED_POINT/2);
        encryptDouble(x * x, encXX);
        encryptDouble(y * y, encYY);
        encryptDouble(z * z, encZZ);
    }


    EncryptedPoint(){};

    EncryptedPoint(double x, double y, double z) {
        encrypt2(x, y, z);
    }

    void squareDistance(mpz_t res, EncryptedPoint other) {
        squareDistance2(res, other);
    }

    void squareDistance1(mpz_t res, EncryptedPoint other) {
        mpz_t tmp1, tmp2, tmp3, tmp4, tmp5,tmp6;
        mpz_inits(tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, NULL);
        Global::pai.add(tmp1, encXX, other.encXX); // x1^2 + x2^2
        Global::pai.add(tmp2, encYY, other.encYY); // y1^2 + y2^2
        Global::pai.add(tmp3, encZZ, other.encZZ); // z1^2 + z2^2
        Global::mul(tmp4, encX4, other.n2x); // -2x1x2
        Global::mul(tmp5, encY4, other.n2y); // -2y1y2
        Global::mul(tmp6, encZ4, other.n2z); // -2z1z2
        Global::pai.add(tmp1, tmp1, tmp2); // x1^2 + x2^2 + y1^2 + y2^2
        Global::pai.add(tmp3, tmp3, tmp4); // z1^2 + z2^2 - 2x1x2
        Global::pai.add(tmp5, tmp5, tmp6); // -2y1y2 - 2z1z2
        Global::pai.add(tmp1, tmp1, tmp3); // x1^2 + x2^2 + y1^2 + y2^2 + z1^2 + z2^2 - 2x1x2
        Global::pai.add(res, tmp1, tmp5); // x1^2 + x2^2 + y1^2 + y2^2 + z1^2 + z2^2 - 2x1x2 - 2y1y2 - 2z1z2
    }

    void squareDistance2(mpz_t res, EncryptedPoint other) {
        mpz_t tmp1, tmp2, tmp3, tmp4, tmp5,tmp6;
        mpz_inits(tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, NULL);
        Global::pai.add(tmp1, encXX, other.encXX); // x1^2 + x2^2
        Global::pai.add(tmp2, encYY, other.encYY); // y1^2 + y2^2
        Global::pai.add(tmp3, encZZ, other.encZZ); // z1^2 + z2^2
        Global::mul(tmp4, encX4, other.encX4); // x1x2
        Global::mul(tmp5, encY4, other.encY4); // y1y2
        Global::mul(tmp6, encZ4, other.encZ4); // z1z2
        Global::pai.scl_mul(tmp4, tmp4, -2); // 2x1x2
        Global::pai.scl_mul(tmp5, tmp5, -2); // 2y1y2
        Global::pai.scl_mul(tmp6, tmp6, -2); // 2z1z2
        Global::pai.add(tmp1, tmp1, tmp2); // x1^2 + x2^2 + y1^2 + y2^2
        Global::pai.add(tmp3, tmp3, tmp4); // z1^2 + z2^2 - 2x1x2
        Global::pai.add(tmp5, tmp5, tmp6); // -2y1y2 - 2z1z2
        Global::pai.add(tmp1, tmp1, tmp3); // x1^2 + x2^2 + y1^2 + y2^2 + z1^2 + z2^2 - 2x1x2
        Global::pai.add(res, tmp1, tmp5); // x1^2 + x2^2 + y1^2 + y2^2 + z1^2 + z2^2 - 2x1x2 - 2y1y2 - 2z1z2
    }

};


#endif //PriCT_ENCRYPTEDPOINT_HPP
