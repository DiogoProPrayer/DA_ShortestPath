#ifndef ENVIRONMENTAL_H
#define ENVIRONMENTAL_H

#include <vector>
#include <utility>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "dijkstra.h"

using namespace std;

// Class environmental to get the environmental routes
class Environmental {
    public:
        struct BestRoute {
            vector<int> drivePath;
            vector<int> walkPath;
            int driveTime = INT_MAX;
            int walkTime = INT_MAX;
        };

        struct AltRoute {
            vector<int> drivePath;
            vector<int> walkPath;
            int driveTime = INT_MAX;
            int walkTime = INT_MAX;
        };

        // Calculate best environmental route
        pair<BestRoute, bool> Environmental::bestRoute(Graph* graph, Node* orig, Node* dest, int maxWalkingTime, vector<int> avoidNodes, vector<pair<Node*, Node*>> avoidEdges);

        // Calculate aproximate environmental route
        pair<BestRoute, AltRoute> Environmental::aprRoute(Graph* graph, Node* orig, Node* dest, vector<int> avoidNodes, vector<pair<Node*, Node*>> avoidEdges);
};

#endif

