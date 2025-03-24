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

using namespace std;

// Calculate best environmental route
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<bool, bool>> Environmental::bestRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
    // Set exceed maximum limit of walking time and abssent of parking true
    bool eml = true; // exceed maximum limit
    bool aop = true; // abssent of parking

    // Remove nodes to be avoided from graph
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges to be avoided from graph
    for (auto& edge : aEdges){ // avoid edges
        g->removeEdge(edge.first, edge.second);
    }

    // Get the best driving and walking routes and their times
    vector<int> bdr; // best driving route
    vector<int> bwr; // best walking route
    int bdt = INT_MAX; // best driving time
    int bwt = INT_MAX; // best walking time

    // Go through all nodes
    for (Node* n : g->getNodes()){ // node

        // Get driving time from origin
        Dijkstra gd; // algorithm
        gd.dijkstra(g, orig, true);

        vector<int> dPath; // driving path

        // Check if possible - continue to next node if not
        if (n->getPath() == nullptr){
            continue;
        }

        // Get driving path from origin to current node
        Node *cn = g->findNode(n); // current node
        cn = cn->getPath();
        while (cn){
            dPath.push_back(cn->getId());
            cn = cn->getPath();
        }
        reverse(dPath.begin(), dPath.end());

        // Get driving time of the current route
        int cdt = n->getDistance(); // current driving time

        // Get walking time 
        Dijkstra gw; // algorithm
        gw.dijkstra(g, n, false);

        vector<int> wPath; // walking path

        // Check if possible - if not continue to next node
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

        // Check if valid - current walking time doesn't exceed maximum walking time and the node is a parking node
        if (cwt < mwt && n->getParking() == 1){

            // Check if the routes are better - total time inferior than hte best total time and if it's equal check if on the current route we walk more
            if ((cdt + cwt < bdt + bwt) || (cdt + cwt == bdt + bwt && cwt > bwt)){
                bdt = cdt; // best driving time = current driving time
                bwt = cwt; // best walking time = current walking time 
                bdr = dPath; // best driving route = driving path
                bwr = wPath; // best walking route = walking path
            } 

            // If it's a valid path then it doesn't exceed maximum limit walking time and also it means it is a parking node
            eml = false;
            aop = false;
        }

        // If it's not a parking node but it doesn't exceed maximum walking limit
        else if (dest->getDistance() < mwt){
            eml = false;
        }

        // If it exceeds maximum walking limit but it's a parking node
        else if (n->getParking() == 1) {
            aop = false;
        }

        // If it fails both conditions
        else{
            continue;
        }
    }

    // Return result - both routes and respestive times, conditions met
    return {{{bdr, bwr}, {bdt, bwt}}, {eml, aop}};
}


// Calculate aproximate environmental route
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<pair<vector<int>, vector<int>>, pair<int, int>>> Environmental::aprRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, bool eml, bool aop){

    // Remove nodes to be avoided from graph
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges to be avoided from graph
    for (auto& edge : aEdges){ // avoid edges
        g->removeEdge(edge.first, edge.second);
    }

    // Get two possible routes and times
    vector<int> fbdr; // first best driving route
    vector<int> fbwr; // first best walking route
    int fbdt = INT_MAX; // first best driving time
    int fbwt = INT_MAX; // first best walking time
    vector<int> sbdr; // second best driving route
    vector<int> sbwr; // second best walking route
    int sbdt = INT_MAX; // second best driving time
    int sbwt = INT_MAX; // second best walking time

    // Go through all nodes
    for (Node* n : g->getNodes()){ // node

        // Get driving time for driving from origin
        Dijkstra gd; // algorithm
        gd.dijkstra(g, orig, true);

        vector<int> dPath; // driving path

        // Check if possible - continue to next node if not
        if (n->getPath() == nullptr){
            continue;
        }

        // Get path for driving route
        Node *cn = g->findNode(n); // current node
        cn = cn->getPath();
        while (cn){
            dPath.push_back(cn->getId());
            cn = cn->getPath();
        }
        reverse(dPath.begin(), dPath.end());

        // Get driving time of current driving route
        int cdt = n->getDistance(); // current driving time

        // Get walking time from current node
        Dijkstra gw; // algortihm
        gw.dijkstra(g, n, false);

        vector<int> wPath; // walking path

        // Check if possible - move to next node if not
        if (dest->getPath() == nullptr){
            continue;
        }
        // Get path for walking route
        cn = g->findNode(dest);
        while (cn){
            wPath.push_back(cn->getId());
            cn = cn->getPath();
        }
        reverse(wPath.begin(), wPath.end());

        // Get walking time for current walking route
        int cwt = dest->getDistance(); // current walking time

        // check if any condition applies
        if ((eml && aop) || (eml && n->getParking() == 1) || (aop && cwt < mwt)){

            // Check if current route is better than the best of the best routes
            if ((cdt + cwt < fbdt + fbwt) || (cdt + cwt == fbdt + fbwt && cwt > fbwt)){
                // Put the best of the best routes as the second best route as well as the times
                sbdt = fbdt;
                sbwt = fbwt;
                sbdr = fbdr;
                sbwr = fbwr;

                // Put the current routes and times as the best of the best routes
                fbdt = cdt;
                fbwt = cwt;
                fbdr = dPath;
                fbwr = wPath;
            }
            
            // Check if it is at least better than the second best route
            else if ((cdt + cwt < sbdt + sbwt) || (cdt + cwt == sbdt + sbwt && cwt > sbwt)){

                // Put the current routes and times as the second best routes
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

        // If the condition isn't met
        else{
            continue;
        }
    }

    // Return result - first best routes and times, second best routes and times
    return {{{fbdr, fbwr}, {fbdt, fbwt}}, {{sbdr, sbwr}, {sbdt, sbwt}}};
}

