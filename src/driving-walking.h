#ifndef DRIVING_WALKING_H
#define DRIVING_WALKING_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include "menu.h"

using namespace std;


struct DrivingWalkingResult {
    vector<int> driving_route;
    vector<int> walking_route;
    int driving_time;
    int walking_time;
    int parking_node;
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
    bool calculateRoute();
};





#endif // DRIVING_WALKING_H