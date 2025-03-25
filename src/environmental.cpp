#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <utility>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "dijkstra.h"
#include "environmental.h"
#include "driving.h"

using namespace std;

// Calculate best environmental route
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, bool> Environmental::bestRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){

    // Get the best driving and walking routes and their times
    vector<int> bdr; // best driving route
    vector<int> bwr; // best walking route
    int bdt = INT_MAX; // best driving time
    int bwt = INT_MAX; // best walking time

    // Set parking nodes available false
    bool park = false;

    // Remove nodes to be avoided from graph
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges to be avoided from graph
    for (auto& edge : aEdges){ // avoid edges
        g->removeEdge(edge.first, edge.second);
    }

    // Get parking nodes
    vector<Node*> parkingNodes;
    for (Node* n : g->getNodes()){
      if (n->getParking() == 1){
        parkingNodes.push_back(n);
        park = true;
      }
    }
    if (!park){
      return {{{bdr, bwr}, {bdt, bwt}}, park};
    }

    // Go through all parking nodes
    for (Node* n : parkingNodes){ // node

        // run the algorithm
        Dijkstra gw; // walking time
        gw.dijkstra(g, n, false);

        // walking path
        vector<int> wPath; // walking path

        // Check if possible and doesn't exceed maximum walking time - continue to the next node if not
        if (dest->getPath() == nullptr || dest->getDistance() > mwt){
            continue;
        }

        // Get walking path
        cn = g->findNode(dest);
        while (cn){
            wPath.push_back(cn->getId());
            cn = cn->getPath();
        }
        reverse(wPath.begin(), wPath.end());

        // Get walking time of route
        int cwt = dest->getDistance(); // current walking time

        // get driving route from origin to node
        pair<vector<int>, int> dr = Driving::indRoute(g, orig, n, true); // driving route

        // get driving path
        vector<int> dPath = dr.first; // walking path

        // Get driving time of the current route
        int cdt = dr.second; // current driving time

        // Check if best
        if ((cdt + cwt < bdt + bwt) || (cdt + cwt == bdt + bwt && cwt > bwt)){
            bdt = cdt;
            bwt = cwt;
            bdr = dPath;
            bwr = wPath;
        }

        // If is no better
        else{
            continue;
        }
    }

    // Return result - both routes and respestive times, conditions met
    return {{{bdr, bwr}, {bdt, bwt}}, park};
}


// Calculate aproximate environmental route
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<pair<vector<int>, vector<int>>, pair<int, int>>> Environmental::aprRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){

    // Get two possible routes and times
    vector<int> fbdr; // first best driving route
    vector<int> fbwr; // first best walking route
    int fbdt = INT_MAX; // first best driving time
    int fbwt = INT_MAX; // first best walking time
    vector<int> sbdr; // second best driving route
    vector<int> sbwr; // second best walking route
    int sbdt = INT_MAX; // second best driving time
    int sbwt = INT_MAX; // second best walking time

    // Remove nodes to be avoided from graph
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges to be avoided from graph
    for (auto& edge : aEdges){ // avoid edges
        g->removeEdge(edge.first, edge.second);
    }

    // Get parking nodes
    vector<Node*> parkingNodes;
    for (Node* n : g->getNodes()){
        if (n->getParking() == 1){
            parkingNodes.push_back(n);
        }
    }

    // Go through all parking nodes
    for (Node* n : parkingNodes){ // node

        // run the algorithm
        Dijkstra gw; // walking time
        gw.dijkstra(g, n, false);

        // walking path
        vector<int> wPath; // walking path

        // Check if possible - continue to the next node if not
        if (dest->getPath() == nullptr){
            continue;
        }

        // Get walking path
        cn = g->findNode(dest);
        while (cn){
            wPath.push_back(cn->getId());
            cn = cn->getPath();
        }
        reverse(wPath.begin(), wPath.end());

        // Get walking time of route
        int cwt = dest->getDistance(); // current walking time

        // get driving route from origin to node
        pair<vector<int>, int> dr = Driving::indRoute(g, orig, n, true); // driving route

        // get driving path
        vector<int> dPath = dr.first; // walking path

        // Get driving time of the current route
        int cdt = dr.second; // current driving time

        // Check if best
        if ((cdt + cwt < fbdt + fbwt) || (cdt + cwt == fbdt + fbwt && cwt > fbwt)){
            fbdt = cdt;
            fbwt = cwt;
            fbdr = dPath;
            fbwr = wPath;
            sbdt = fbdt;
            sbwt = fbwt;
            sbdr = fbdr;
            sbwr = fbwr;
        }

        // Check if second best
        else if ((cdt + cwt < sbdt + sbwt) || (cdt + cwt == sbdt + sbwt && cwt > sbwt)){
            sbdt = cdt;
            sbwt = cwt;
            sbdr = dPath;
            sbwr = wPath;
        }

        // If is no better
        else{
            continue;
        }
    }

    // Return result - first best routes and times, second best routes and times
    return {{{fbdr, fbwr}, {fbdt, fbwt}}, {{sbdr, sbwr}, {sbdt, sbwt}}};
}

