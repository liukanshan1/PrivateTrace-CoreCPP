//
// Created by 12695 on 2023/3/18.
//

#ifndef C___TRAJECTORYREADER_H
#define C___TRAJECTORYREADER_H

#include <string>
#include <iostream>
#include "TimeLocationData.hpp"
#include <vector>
#include <fstream>
#include "sstream"
#include <ctime>
#include <iomanip>
#include "Trajectory.hpp"

using namespace std;

int timeIntervalCount = 0;
int maxIntervalNum = 0;
int tcount = 0;

class TrajectoryReader {
private:
    string path;
    ifstream file;

public:
    TrajectoryReader(const string& path) : path(path) {
        file.open(path, ios::in);
        if (! file.is_open()) {
            cout << "File open failed" << endl;
            exit(1);
        }
        for (int i = 0; i < 6; i++) {
            string line;
            getline(file, line);
        }
    }

    string hasNext() {
        string line;
        getline(file, line);
        return line;
    }

    TimeLocationData* next(string line) {
        istringstream iss(line);
        string token;
        vector <string> tokens;
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        double lat = stod(tokens[0]);
        double lon = stod(tokens[1]);
        double altitude = stod(tokens[3]); // Altitude in feet
        altitude = 0;
        string time = tokens[5] + ' ' + tokens[6];
        tm tm = {};
        istringstream ss(time);
        ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
        time_t date = mktime(&tm);
        if (Global::IGNORE_DATE) {
            tm.tm_year = 2008 - 1900;
            tm.tm_mon = 6 - 1;
            tm.tm_mday = 24;
            date = mktime(&tm);
        }
        return new TimeLocationData(Location(lat, lon, altitude), tm);
    }

    Trajectory load() {
        tcount++;
        vector <TimeLocationData*> tlds;
        TimeLocationData* pTLD = nullptr;
        tm previousDate = {};
        double rad = 0;
        string line = hasNext();
        int tmpIntervalNum = 0;
        while (line != "") {
            if (Global::originPointUpperboundFlag) {
                if (Global::originPoint + 1 > Global::originPointUpperbound1) {
                    if (tcount > 0) {
                        cout<< tcount <<endl;
                        tcount = -1000000;
                    }
                    break;
                }
            } else {
                if (Global::originPoint + 1 > Global::originPointUpperbound2) {
                    if (tcount > 0) {
                        cout<< tcount <<endl;
                        tcount = -1000000;
                    }
                    break;
                }
            }
            Global::originPoint++;
            TimeLocationData* cTLD = next(line);
            tm currentDate = Global::getStart(cTLD->getDate());
            if (Global::equal(currentDate, previousDate)) {
                tmpIntervalNum++;
                rad = max(rad, cTLD->getLoc().distance(pTLD->getLoc()));
                if (rad < Global::RADIUS * 1.5) {
                    line = hasNext();
                    continue;
                }
            } else {
                timeIntervalCount++;
                maxIntervalNum = max(tmpIntervalNum, maxIntervalNum);
                tmpIntervalNum = 0;
            }
            if (rad > Global::RADIUS * 3) {
                Global::originPoint--;
                cout << "Reject: " << path << endl;
                break;
            }
            if (rad > Global::RADIUS * 2) {
                TimeLocationData* mTLD = new TimeLocationData(Location(
                        (cTLD->getLoc().getLatitude() + pTLD->getLoc().getLatitude()) / 2.0,
                        (cTLD->getLoc().getLongitude() + pTLD->getLoc().getLongitude()) / 2.0
                ), currentDate);
                mTLD->setPrevious(pTLD);
                mTLD->setNext(cTLD);
                tlds.push_back(mTLD);
                pTLD = mTLD;
                Global::encodePoint++;
            }
            rad = 0;
            cTLD->setDate(currentDate);
            cTLD->setPrevious(pTLD);
            if (pTLD != nullptr) {
                pTLD->setNext(cTLD);
            }
            tlds.push_back(cTLD);
            pTLD = cTLD;
            previousDate = currentDate;
            line = hasNext();
            Global::encodePoint++;
        }
        return Trajectory(tlds, path);
    }
};

bool check(Trajectory t) {
    Circle pc = t.getTLDs()[0]->getCircle();
    for (TimeLocationData* tld : t.getTLDs()) {
        Circle cc = tld->getCircle();
        if (Point::distance(cc.getCenter(), pc.getCenter()) > Global::RADIUS * 3) {
            // cout << Point::distance(cc.getCenter(), pc.getCenter()) << " " << tld.getDate() << endl;
            return false;
        }
        pc = cc;
    }
    return true;
}
#endif //C___TRAJECTORYREADER_H
