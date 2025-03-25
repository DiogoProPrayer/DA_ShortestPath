#ifndef DRIVING_WALKING_H
#define DRIVING_WALKING_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include "menu.h"

using namespace std;


struct DrivingWalkingResult {
    vector<int> driving_route = {};
    vector<int> walking_route = {};
    int driving_time = 0;
    int walking_time = 0;
    int parking_node = 0;

    bool no_parking = false;
    bool no_range = false;
};

struct CompareNodeWalking {
    bool operator()(Node* a, Node* b) {
        return a->getWalkingDist() > b->getWalkingDist();
    }
};

struct CompareNodeDriving {
    bool operator()(Node* a, Node* b) {
        return a->getDist() > b->getDist();
    }
};

class DrivingWalking {
private:
    DrivingWalkingResult result;
    DrivingWalkingResult alternative1;
    DrivingWalkingResult alternative2;


    Graph graph;
    int source;
    int destination;
    int maxWalkTime;
    unordered_set<int> avoidNodes;
    unordered_set<pair<int, int>, pair_hash> avoidSegments;

    vector<Node *> walking_to_parks();

public:
    DrivingWalking(Graph graph,int source, int destination, int maxWalkTime, unordered_set<int> avoidNodes, unordered_set<pair<int, int>, pair_hash> avoidSegments);
    pair<DrivingWalkingResult, DrivingWalkingResult> alternativeRoutes();
    DrivingWalkingResult calculateRoute();
};


#endif // DRIVING_WALKING_H