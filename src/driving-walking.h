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
    double walking_time = 0;
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
    double maxWalkTime;
    unordered_set<int> avoidNodes;
    unordered_set<pair<int, int>, pair_hash> avoidSegments;

    /**
    * @brief Gets parking nodes within max walking time
    * @details Complexity O(E log V)
    * @return Set of parking nodes
    */
    unordered_set<Node *> walking_to_parks();

    /**
    * @brief Calculates driving route to valid parking nodes
    * @details Complexity O(E log V)
    * @param parkingNodes Set of valid parking nodes
    * @return True if possible, false otherwise
    */
    bool driving_to_parks(unordered_set<Node *> parkingNodes);

public:

    /**
    * @brief DrivingWalking constructor
    * @param graph The graph representing the map
    * @param source The starting node ID for driving
    * @param maxWalkTime Maximum walking time allowed
    * @param avoidNodes Set of node IDs to avoid
    * @param avoidSegments Set of segments (pair of node IDs) to avoid
    */
    DrivingWalking(Graph &graph,int source, int destination, double maxWalkTime, unordered_set<int> avoidNodes, unordered_set<pair<int, int>, pair_hash> avoidSegments);

    /**
    * @brief Calculates the complete driving and walking rout
    * @details Complexity O(E log V)
    * @return DrivingWalkingResult - routes and times
    */
    pair<DrivingWalkingResult, DrivingWalkingResult> alternativeRoutes();

    /**
    * @brief Calculates alternative routes by relaxing restrictions
    * @details Complexity O((E log V))
    * @return Pair of DrivingWalkingResult - 2 alternative routes
    */
    DrivingWalkingResult calculateRoute();
};


#endif // DRIVING_WALKING_H