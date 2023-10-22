#include <iostream>
#include "Data/TrajectoryReader.hpp"
#include <functional>
#include "Protocol/CCircleTree.hpp"
#include "Utils/threadPool.h"

using namespace std;

EncTrajectory encTraj(Trajectory traj) {
    return traj.encrypt();
}

void ccInit(ConcentricCircles *cc) {
    cc->init();
}

string ctCompare(CCircleTree *ct, EncTrajectory et) {
    if (!ct->compare(et)) {
        return et.getName();
    }
    return "";
}

int main() {
    cout << endl;
    vector<string> positivePaths = ls("../../Geolife Trajectories 1.3/Data/001/Trajectory/");
    vector<Trajectory> pTraj;
    for (auto s: positivePaths) {
        TrajectoryReader reader(s);
        pTraj.push_back(reader.load());
    }
    cout << "Positive Trajectories loaded" << endl;
    cout << "Positive Enc Point Num: " << Global::encodePoint << endl << endl;
    Global::originPoint = 0;
    Global::encodePoint = 0;
    vector<string> negativePaths = ls("../../Geolife Trajectories 1.3/Data/008/Trajectory/");
    vector<Trajectory> nTraj;
    for (auto s: negativePaths) {
        TrajectoryReader reader(s);
        nTraj.push_back(reader.load());
    }
    cout << "Negative Trajectories loaded" << endl;
    cout << "Negative Trajectories size: " << nTraj.size() << endl;
    cout << "Negative Point Num: " << Global::originPoint << endl;
    cout << "Negative Enc Point Num: " << Global::encodePoint << endl << endl;
    Global::originPoint = 0;
    Global::encodePoint = 0;

    vector<EncTrajectory> encPTraj;
    for (auto t: pTraj) {
        encPTraj.push_back(t.encrypt());
    }
    cout << "Positive Encrypted Trajectories loaded" << endl;
    vector<EncTrajectory> encNTraj;
    for (auto t: nTraj) {
        encNTraj.push_back(t.encrypt());
    }
    cout << "Negative Encrypted Trajectories loaded" << endl;

    cout << "-------------------" << endl;
    int treePointCount = 0;
    CCircleTree *tree = new CCircleTree();
    vector<Trajectory> traj;
    int no = 0;
    double a1, b1, c1;
    while (!encPTraj.empty()) {
        auto tmp = encPTraj[encPTraj.size() - 1];
        encPTraj.pop_back();
        traj.push_back(pTraj[pTraj.size() - 1]);
        pTraj.pop_back();
        tree->add(tmp);
        treePointCount += tmp.getETLDs().size();
        cout << "No." << no++ << " / " << positivePaths.size() << endl;
        cout << "Tree Point Count: " << treePointCount << endl;
        a1 = treePointCount;

        auto ccs = tree->ccTree;
        auto b = clock();
        for (auto cc: ccs) {
            cc.second->init();
        }
        auto e = clock();
        for (auto cc: ccs) {
            pruneSize[cc.second] = cc.second->size();
        }
        printf("Tree initialized time is  ------  %f s\n", ((double) (e - b)) / CLOCKS_PER_SEC);
        b1 = ((double) (e - b)) / CLOCKS_PER_SEC;

        b = clock();
        for (auto t: encNTraj) {
            tree->compare(t);
        }
        e = clock();
        printf("Compare time is  ------  %f s\n", ((double) (e - b)) / CLOCKS_PER_SEC);
        c1 = ((double) (e - b)) / CLOCKS_PER_SEC;

        std::ofstream outfile;
        outfile.open("res.csv", std::ios_base::app);
        outfile << a1 << "," << b1 << "," << c1 << endl;
        outfile.close();
    }

}
