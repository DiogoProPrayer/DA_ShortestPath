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

        // Calculate main environmental route
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<bool, bool>> mainEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);

        // Calculate environmental route with no walking limit
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> nwlEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);

        // Calculate environmental route with any parking option
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> apoEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);

        // Calculate environmental route with no rules
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> nrEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);
};

#endif
