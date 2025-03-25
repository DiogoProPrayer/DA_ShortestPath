#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <utility>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "dijkstra.h"
#include "driving.h"

using namespace std;

// Calculate independent driving route
pair<vector<int>, int> Driving::indRoute(Graph* g, Node* orig, Node* dest, bool best){

    // Get driving time
    Dijkstra gd; // algorithm
    gd.dijkstra(g, orig, true);

    // path to return
    vector<int> path;
    
    // Check if possible - return distance -1 if not
    if (dest->getPath() == nullptr || dest->getParking() == 0){
        return {path, -1};
    }

    // Get path
    Node *cn = g->findNode(dest); // current node
    while (cn){
        path.push_back(cn->getId());
        cn = cn->getPath();
    }
    reverse(path.begin(), path.end());

    // Return result - path and distance
    if (best) {
        return {path, dest->getDistance()};
    }

    // Remove nodes used in main driving route from graph
    for (int i = 1; i < path.size()-1; i++){
        g->removeNode(path[i]);
    }

    // Get driving time for alternative route
    gd.dijkstra(g, orig, true);

    // Alternative path
    vector<int> apath;

    // Check if possible - return distance -1 if not
    if (dest->getPath() == nullptr || dest->getParking() == 0){
        return {apath, -1};
    }

    // Get path for alternative route
    cn = g->findNode(dest);
    while (cn){
        apath.push_back(cn->getId());
        cn = cn->getPath();
    }
    reverse(apath.begin(), apath.end());

    // Return result - path and distance
    return {apath, dest->getDistance()};
}

// Calculate restricted driving route
pair<vector<int>, int> Driving::resRoute(Graph* g, Node* orig, Node* dest, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, Node* iNode){

    // Remove nodes that can't be used from graph - avoid nodes
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges that can't be used from graph - avoid edges
    for (auto& edge : aEdges){ // avoid edges
        g->removeEdge(edge.first, edge.second);
    }

    // Check if there is a node to be included - include node
    if (iNode == nullptr) { // no node to be included
        return indRoute(g, orig, dest, true)
    }

    else {

        // total final distance
        int dist = 0;

        // Get driving time from node to be included
        Dijkstra gd; // algorithm
        gd.dijkstra(g, iNode, true);

        // path to return
        vector<int> path;

        // Check if possible - if not distance -1
        if (dest->getPath() == nullptr || dest->getParking() == 0){
            return {path, -1};
        }

        // Get path from destination to node to include
        Node *cn = g->findNode(dest); // current node
        while (cn){
            path.push_back(cn->getId());
            cn = cn->getPath();
        }

        // sum distance
        dist += dest->getDistance();

        // Get driving time from origin
        gd.dijkstra(g, orig);

        // Check if possible - distance -1 if not
        if (iNode->getPath() == nullptr){ // can't include node
            return {path, -1};
        }

        // Get path from node to be included to origin - not including node to include again
        cn = g->findNode(iNode);
        cn = cn->getPath();
        while (cn){
            path.push_back(cn->getId());
            cn = cn->getPath();
        }

        // sum distance
        dist += iNode->getDistance();

        // final path
        reverse(path.begin(), path.end());

        // Return result
        return {path, dist};
    }
}