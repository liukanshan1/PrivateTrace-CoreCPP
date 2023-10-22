//
// Created by 12695 on 2023/3/18.
//

#ifndef PriCT_GLOBAL_HPP
#define PriCT_GLOBAL_HPP

#include "SOCI/paillier.h"
#include "SOCI/soci.h"
#include <iostream>
namespace Global {
    const int THREAD = 1;
    const bool IGNORE_DATE = true;
    const int INTERVAL = 10;
    const double RADIUS = 200.0;
    const double RADIUS2 = RADIUS * RADIUS;
    const double COMPARE_DISTANCE[] = {1200 * 1200.0};
    const int PRUNE_NUM[] = {0, 2};
    const int PRUNE_NUM_LENGTH = sizeof(PRUNE_NUM) / sizeof(int);
    const int COMPARE_DISTANCE_LENGTH = sizeof(COMPARE_DISTANCE) / sizeof(double);
    int originPoint = 0;
    int originPointUpperbound1 = 60000;
    int originPointUpperbound2 = 40000;
    bool originPointUpperboundFlag = true;
    int encodePoint = 0;
    Paillier pai;
    int init() {
        setrandom();
        pai.keygen(256 * 2);
        std::cout << "THREAD: " << THREAD << std::endl;
        std::cout << "IGNORE_DATE: " << IGNORE_DATE << std::endl;
        std::cout << "INTERVAL: " << INTERVAL << std::endl;
        std::cout << "RADIUS: " << RADIUS << std::endl;
        std::cout << "COMPARE_DISTANCE: ";
        for (int i = 0; i < sizeof(COMPARE_DISTANCE) / sizeof(double); i++) {
            std::cout << COMPARE_DISTANCE[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "PRUNE_NUM: ";
        for (int i = 0; i < sizeof(PRUNE_NUM) / sizeof(int); i++) {
            std::cout << PRUNE_NUM[i] << " ";
        }
        std::cout << std::endl;
        return 0;
    }
    int _ = init();
    const int sigma = 128;
    PaillierThdPrivateKey* psk = thdkeygen(pai.prikey, sigma);
    PaillierThd cp(psk[0], pai.pubkey);
    PaillierThd csp(psk[1], pai.pubkey);
    soci::seccomp sc;
    void mul(mpz_t res, mpz_t cx, mpz_t cy) {
        sc.smul(res, cx, cy, cp, csp);
    }
    int scmp(mpz_t cx, mpz_t cy){
        mpz_t res;
        mpz_init(res);
        sc.scmp(res, cx, cy, cp, csp);
        pai.decrypt(res, res);
        return mpz_get_si(res);
    }
    tm getStart(tm d) {
        d.tm_sec = 0;
        d.tm_min = d.tm_min - d.tm_min % Global::INTERVAL;
        return d;
    }
    bool equal(tm d1, tm d2) {
        return d1.tm_year == d2.tm_year && d1.tm_mon == d2.tm_mon && d1.tm_mday == d2.tm_mday && d1.tm_hour == d2.tm_hour && d1.tm_min == d2.tm_min;
    }
}
#endif //PriCT_GLOBAL_HPP
