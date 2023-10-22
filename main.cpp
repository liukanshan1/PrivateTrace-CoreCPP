#include <iostream>
#include "Data/TrajectoryReader.hpp"
#include <functional>
#include "Protocol/CCircleTree.hpp"
#include "Utils/threadPool.h"

using namespace std;


int main() {
    cout << endl;
    vector<string> positivePaths = ls("../../Geolife Trajectories 1.3/Data/003/Trajectory/");
    vector<Trajectory> pTraj;
    for (auto s: positivePaths) {
        TrajectoryReader reader(s);
        pTraj.push_back(reader.load());
    }
    cout << "Positive Trajectories loaded" << endl;
    cout << "Positive Trajectories size: " << pTraj.size() << endl;
    cout << "Positive Point Num: " << Global::originPoint << endl;
    cout << "Positive Enc Point Num: " << Global::encodePoint << endl;
    Global::originPoint = 0;
    Global::encodePoint = 0;
    cout << "IntervalCount: " << timeIntervalCount << endl;
    cout << "MaxIntervalNum: " << maxIntervalNum << endl << endl;
    timeIntervalCount = 0;
    maxIntervalNum = 0;
    tcount = 0;
    Global::originPointUpperboundFlag = false;

    vector<string> negativePaths = ls("../../Geolife Trajectories 1.3/Data/002/Trajectory/");
    vector<Trajectory> nTraj;
    for (auto s: negativePaths) {
        TrajectoryReader reader(s);
        nTraj.push_back(reader.load());
    }
    cout << "Negative Trajectories loaded" << endl;
    cout << "Negative Trajectories size: " << nTraj.size() << endl;
    cout << "Negative Point Num: " << Global::originPoint << endl;
    cout << "Negative Enc Point Num: " << Global::encodePoint << endl;
    Global::originPoint = 0;
    Global::encodePoint = 0;
    cout << "IntervalCount: " << timeIntervalCount << endl;
    cout << "MaxIntervalNum: " << maxIntervalNum << endl << endl;
    timeIntervalCount = 0;
    maxIntervalNum = 0;

    vector<EncTrajectory> encPTraj;
    auto b = clock();
    for (auto t: pTraj) {
        encPTraj.push_back(t.encrypt());
    }
    auto e = clock();
    cout << "Positive Encrypted Trajectories loaded" << endl;
    printf("time is  ------  %f ms\n", ((double) (e - b)) / 1 * 1000 / CLOCKS_PER_SEC);
    printf("time is  ------  %f s\n\n", ((double) (e - b)) / CLOCKS_PER_SEC);

    vector<EncTrajectory> encNTraj;
    b = clock();
    for (auto t: nTraj) {
        encNTraj.push_back(t.encrypt());
    }
    e = clock();
    cout << "Negative Encrypted Trajectories loaded" << endl;
    printf("time is  ------  %f ms\n", ((double) (e - b)) / 1 * 1000 / CLOCKS_PER_SEC);
    printf("time is  ------  %f s\n", ((double) (e - b)) / CLOCKS_PER_SEC);
    int byte = 0;
    for (auto t: encNTraj) {
        for (auto p: t.getETLDs()) {
            auto c = p->getCircle().getEncryptedPoint();
            FILE* f = fopen("./comm.bin", "wb");
            byte += mpz_out_raw(f, c.encX4);
            byte += mpz_out_raw(f, c.encY4);
            byte += mpz_out_raw(f, c.encZ4);
            byte += mpz_out_raw(f, c.encXX);
            byte += mpz_out_raw(f, c.encYY);
            byte += mpz_out_raw(f, c.encZZ);
        }
    }
    cout << "Client Comm Byte: " << byte << endl;
    cout << "Client Comm mb: " << byte / 1024.0 / 1024.0 << endl<<endl;

    CCircleTree *tree = new CCircleTree();
    for (int i = 0; i < encPTraj.size(); ++i) {
        tree->add(encPTraj[i]);
    }
    cout << "Positive Encrypted Trajectories added" << endl;

    auto ccs = tree->ccTree;
    b = clock();
    for (auto cc: ccs) {
        cc.second->init();
    }
    e = clock();
    for (auto cc: ccs) {
        pruneSize[cc.second] = cc.second->size();
    }
    cout << "Tree initialized" << endl;
    printf("time is  ------  %f ms\n", ((double) (e - b)) / 1 * 1000 / CLOCKS_PER_SEC);
    printf("time is  ------  %f s\n\n", ((double) (e - b)) / CLOCKS_PER_SEC);
#if COMM
    cout<< "Mul Comm Call: "<< soci::mulCount / 2 << endl;
    cout<< "Mul Comm Count: "<< soci::mulCount << endl;
    cout<< "Mul Comm Byte: "<< soci::mulByte << endl;
    cout << "Cmp Comm Call: " << soci::cmpCount / 2 << endl;
    cout << "Cmp Comm Count: " << soci::cmpCount << endl;
    cout << "Cmp Comm Byte: " << soci::cmpByte << endl;
    cout << "----------------------" << endl;
    cout << "Mul Comm kb: " << soci::mulByte / 1024.0 << endl;
    cout << "Cmp Comm kb: " << soci::cmpByte / 1024.0 << endl;
    cout << "Mul Comm mb: " << soci::mulByte / 1024.0 / 1024.0 << endl;
    cout << "Cmp Comm mb: " << soci::cmpByte / 1024.0 / 1024.0 << endl;
    cout << soci::mulByte / 1024.0 / 1024.0  + soci::cmpByte / 1024.0 / 1024.0 << endl;
    soci::mulByte = 0;
    soci::mulCount = 0;
    soci::cmpByte = 0;
    soci::cmpCount = 0;
#endif

    b = clock();
    for (auto t: encNTraj) {
        if (!tree->compare(t)) {
            cout << t.getName() << endl;
        }
    }
    e = clock();
    cout << "Compare finished" << endl;
    printf("time is  ------  %f ms\n", ((double) (e - b)) / 1 * 1000 / CLOCKS_PER_SEC);
    printf("time is  ------  %f s\n\n", ((double) (e - b)) / CLOCKS_PER_SEC);

    for (auto &i: nTraj) {
        for (auto &j: pTraj) {
            if (Trajectory::isIntersect(i, j)) {
                cout << i.getName() << " " << j.getName() << endl;
                break;
            }
        }
    }

#if COMM
    cout<< "Mul Comm Call: "<< soci::mulCount / 2 << endl;
    cout<< "Mul Comm Count: "<< soci::mulCount << endl;
    cout<< "Mul Comm Byte: "<< soci::mulByte << endl;
    cout << "Cmp Comm Call: " << soci::cmpCount / 2 << endl;
    cout << "Cmp Comm Count: " << soci::cmpCount << endl;
    cout << "Cmp Comm Byte: " << soci::cmpByte << endl;
    cout << "----------------------" << endl;
    cout << "Mul Comm kb: " << soci::mulByte / 1024.0 << endl;
    cout << "Cmp Comm kb: " << soci::cmpByte / 1024.0 << endl;
    cout << "Mul Comm mb: " << soci::mulByte / 1024.0 / 1024.0 << endl;
    cout << "Cmp Comm mb: " << soci::cmpByte / 1024.0 / 1024.0 << endl;
    cout << soci::mulByte / 1024.0 / 1024.0  + soci::cmpByte / 1024.0 / 1024.0 << endl;
#endif
}
