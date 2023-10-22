//
// Created by lks on 23-3-19.
//
#include "Data/TrajectoryReader.hpp"
#include <iostream>
#include "Protocol/CCircleTree.hpp"
using namespace std;
int main(){
    string positivePaths[5] = {
            "../../Geolife Trajectories 1.3/Data/001/Trajectory/20081023234104.plt",
            "../../Geolife Trajectories 1.3/Data/001/Trajectory/20081208001534.plt",
            "../../Geolife Trajectories 1.3/Data/001/Trajectory/20081210080559.plt",
            "../../Geolife Trajectories 1.3/Data/001/Trajectory/20081205002359.plt",
            "../../Geolife Trajectories 1.3/Data/001/Trajectory/20081117042454.plt"
    };
    vector<Trajectory> pTraj;
    for (int i = 0; i < 5; i++) {
        TrajectoryReader reader(positivePaths[i]);
        pTraj.push_back(reader.load());
    }
    cout << "Positive Trajectories loaded" << endl;
    string negativePaths[2] = {
            "../../Geolife Trajectories 1.3/Data/001/Trajectory/20081023234104.plt",
            "../../Geolife Trajectories 1.3/Data/040/Trajectory/20090213051231.plt",
    };
    vector<Trajectory> nTraj;
    for (int i = 0; i < 2; i++) {
        TrajectoryReader reader(negativePaths[i]);
        nTraj.push_back(reader.load());
    }
    cout << "Negative Trajectories loaded" << endl;
    vector<EncTrajectory> encPTraj;
    for (int i = 0; i < 5; i++) {
        encPTraj.push_back(pTraj[i].encrypt());
    }
    cout << "Positive Encrypted Trajectories loaded" << endl;
    vector<EncTrajectory> encNTraj;
    for (int i = 0; i < 2; i++) {
        encNTraj.push_back(nTraj[i].encrypt());
    }
    cout << "Negative Encrypted Trajectories loaded" << endl;
    CCircleTree* tree = new CCircleTree();
    for (int i = 0; i < 5; ++i) {
        tree->add(encPTraj[i]);
    }
    cout << "Positive Encrypted Trajectories added" << endl;
    tree->init();
    cout << "Tree initialized" << endl;
    for (int i = 0; i < 2; ++i) {
        cout<< tree->compare(encNTraj[i]) << endl;
    }
//    for (int i = 0; i < 2; ++i) {
//        auto tlds = nTraj[i].getTLDs();
//        for (int j = 0; j < 5; ++j) {
//            auto etlds = pTraj[j].getTLDs();
//            for (int k = 0; k < tlds.size(); ++k) {
//                for (int l = 0; l < etlds.size(); ++l) {
//                    if (tlds[k]->getCircle().isIntersect(etlds[l]->getCircle())) {
//                        cout << nTraj[i].getName() << endl;
//                        goto L;
//                    }
//                }
//            }
//        }
//        L:;
//    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (Trajectory::isIntersect(nTraj[i], pTraj[j])){
                cout << nTraj[i].getName() << " " << pTraj[j].getName() << endl;
                break;
            }
        }
    }
}