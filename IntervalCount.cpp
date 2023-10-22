//
// Created by lks on 23-3-29.
//
#include <iostream>
#include "Data/TrajectoryReader.hpp"
#include <functional>
#include "Protocol/CCircleTree.hpp"
#include "Utils/threadPool.h"

int main() {
    int maxi = 0;
    cout << endl;
    std::threadpool executor{Global::THREAD};
    for (int i = 10; i < 100; ++i) {
        vector<string> positivePaths = ls("../../Geolife Trajectories 1.3/Data/0" + to_string(i) +"/Trajectory/");
        vector<Trajectory> pTraj;
        for (auto s: positivePaths) {
            TrajectoryReader reader(s);
            pTraj.push_back(reader.load());
        }
        cout << "MaxIntervalNum: " << maxIntervalNum << endl << endl;
    }

}