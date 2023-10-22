//
// Created by 12695 on 2023/3/18.
//
#include <algorithm>
#include "Data/TrajectoryReader.hpp"
int main() {
    vector<string> positivePaths = ls("../../Geolife Trajectories 1.3/Data/004/Trajectory/");
    vector<Trajectory> pTraj;
    for (auto s: positivePaths) {
        TrajectoryReader reader(s);
        pTraj.push_back(reader.load());
    }
    for (auto t: pTraj) {
        auto tlds = t.getTLDs();
        for (int i = 0; i < tlds.size() - 1; ++i) {
            double tr = tlds[i]->getLoc().distance(tlds[i + 1]->getLoc());
            double act = tlds[i]->getLoc().encodeDistance(tlds[i + 1]->getLoc());
            double error = abs(tr - act) / tr;
            cout << (int)tr/50 << "," << error << endl;
//            cout<<tlds[i]->getLoc().distance(tlds[i + 1]->getLoc())<<",";
//            cout<<tlds[i]->getLoc().encodeDistance(tlds[i + 1]->getLoc())<<endl;
        }
    }
//    auto eTrajectory = trajectory.encrypt();
//    auto eTlds = eTrajectory.getETLDs();
//    // Test Enc Circle Intersect
//    for (int i = 0; i < eTlds.size() - 1; ++i) {
//        cout<<eTlds[i]->getCircle().isIntersect(eTlds[i + 1]->getCircle())<<" ";
//        cout<<tlds[i]->getCircle().isIntersect(tlds[i + 1]->getCircle())<<endl;
//    }
//    cout<<eTlds[0]->getCircle().isIntersect(eTlds[9]->getCircle())<<" ";
//    cout<<tlds[0]->getCircle().isIntersect(tlds[9]->getCircle())<<endl;
//    // Test Enc Circle Prune Number
//    mpz_t sqd;
//    mpz_init(sqd);
//    for (int i = 0; i < eTlds.size() - 5; ++i) {
//        cout<<eTlds[i]->getCircle().howFarAway(eTlds[i + 5]->getCircle(), sqd)<<" ";
//        cout<<pow((tlds[i]->getCircle().getCenter().distance(tlds[i + 5]->getCircle().getCenter())), 2)<<" ";
//        Global::pai.decrypt(sqd, sqd);
//        cout<<mpz_get_d(sqd) / 100000000<<endl;
//    }
//    // Test Enc Square distance
//    vector<EncSquareDistance> esds;
//    vector<double> sqds;
//    for (int i = 0; i < eTlds.size() - 1; ++i) {
//        esds.push_back(eTlds[i]->getCircle().encSquareDistance(eTlds[i + 1]->getCircle()));
//        sqds.push_back(pow(tlds[i]->getCircle().getCenter().distance(tlds[i + 1]->getCircle().getCenter()), 2));
//    }
//    sort(esds.begin(), esds.end());
//    sort(sqds.begin(), sqds.end());
//    for (int i = 0; i < esds.size(); ++i) {
//        cout<<esds[i].getSquareDistance() / 100000000<<" ";
//        cout<<sqds[i]<<endl;
//    }


//    // Test Enc Square Distance
//    Point p(100.3, 250, 300);
//    Point q(106, 200.5, 300.99);
//    cout<<p.distance(q) * p.distance(q)<<endl;
//    EncryptedPoint ep = p.encrypt();
//    EncryptedPoint eq = q.encrypt();
//    mpz_t res;
//    mpz_init(res);
//    ep.squareDistance(res, eq);
//    Global::pai.decrypt(res, res);
//    cout<<mpz_get_d(res) / 100000000<<endl;
//    Circle c(p, 100000);
//    Circle d(q, 100000);
//    // Test Enc Circle Distance
//    EncryptedCircle ec = c.encrypt();
//    EncryptedCircle ed = d.encrypt();
//    mpz_t res2;
//    //mpz_init(res2);
//    mpz_inits(res2, NULL);
//    ec.squareDistance(res2, ed);
//    Global::pai.decrypt(res2, res2);
//    cout<<mpz_get_d(res2) / 100000000<<endl;
//    cout<<ec.isIntersect(ed)<<endl;
    return 0;
}