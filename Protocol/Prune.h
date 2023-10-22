//
// Created by lks on 23-3-20.
//

#ifndef PRICT_PRUNE_H
#define PRICT_PRUNE_H

#include <map>

class ConcentricCircles;
map<ConcentricCircles *, int> pruneSize;

class PruneFlag {
private:
    std::map<ConcentricCircles *, int *> flags;
public:
    void refresh() {
        for (auto & t: pruneSize) {
            flags[t.first] = new int[t.second];
        }
    }

    void prune(ConcentricCircles *cc, int index) {
        flags[cc][index] = 2;
    }

    void unprune(ConcentricCircles *cc, int index) {
        flags[cc][index] = 0;
    }

    void getprune(ConcentricCircles *cc, int index) {
        flags[cc][index] -= 1;
    }

    bool getPruned(ConcentricCircles *cc, int index) {
        return flags[cc][index] > 0;
    }
};

thread_local PruneFlag p;
#endif //PRICT_PRUNE_H
