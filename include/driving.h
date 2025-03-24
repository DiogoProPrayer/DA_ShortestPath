#ifndef DRIVING_H
#define DRIVING_H

#include <vector>
#include <utility>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "dijkstra.h"

using namespace std;

// Class driving to get the driving routes
class Driving {
    public:

        // Calculate independent driving route
        pair<vector<int>, int> indRoute(Graph* g, Node* orig, Node* dest, bool best);

        // Calculate restricted driving route
        pair<vector<int>, int> resRoute(Graph* g, Node* orig, Node* dest, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, Node* iNode);
};

#endif
