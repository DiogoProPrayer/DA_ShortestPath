#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <utility>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "getDriving.h"
#include "getWalking.h"
#include "route.h"

using namespace std;

// Calculate best driving route
pair<vector<int>, int> Route::bestDrivingRoute(Graph* g, Node* orig, Node* dest){
    // Get driving time
    GetDriving gd; // get driving
    gd.dijkstra(g, orig);

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
    return {path, dest->getDistance()};
}

// Calculate alternative driving route
pair<vector<int>, int> Route::altDrivingRoute(Graph* g, Node* orig, Node* dest){
    // Get driving time of main driving route
    GetDriving gd; // get driving
    gd.dijkstra(g, orig);

    vector<int> tempPath; // temporary path

    // Check if possible - return distance -1 if not
    if (dest->getPath() == nullptr || dest->getParking() == 0){
        return {tempPath, -1};
    }

    // Get path for main driving route
    Node *cn = g->findNode(dest); // current node
    while (cn){
        tempPath.push_back(cn->getId());
        cn = cn->getPath();
    }
    reverse(tempPath.begin(), tempPath.end());

    // Remove nodes used in main driving route from graph
    for (int i = 1; i < tempPath.size()-1; i++){
        g->removeNode(tempPath[i]);
    }
    
    // Get driving time for alternative route
    gd.dijkstra(g, orig);

    vector<int> path;

    // Check if possible - return distance -1 if not
    if (dest->getPath() == nullptr || dest->getParking() == 0){
        return {path, -1};
    }

    // Get path for alternative route
    cn = g->findNode(dest);
    while (cn){
        path.push_back(cn->getId());
        cn = cn->getPath();
    }
    reverse(path.begin(), path.end());

    // Return result - path and distance
    return {path, dest->getDistance()};
}     

// Calculate restricted driving route
pair<vector<int>, int> Route::resDrivingRoute(Graph* g, Node* orig, Node* dest, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, Node* iNode){

    // Remove nodes that can't be used from graph - avoid nodes
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges that can't be used from graph - avoid edges
    for (auto& edge : aEdges){ // avoid edges
        g->removeEdge(edge.first, edge.second);
    }

    // Check if there is a node to be included - include node
    if (iNode == nullptr) { // include node

        // Get driving time
        GetDriving gd; // get driving
        gd.dijkstra(g, orig);

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
        return {path, dest->getDistance()};
    }

    else {

        // Get driving time from node to be included
        GetDriving gd; // get driving
        gd.dijkstra(g, iNode);
        
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

        // Get driving time from origin
        gd.dijkstra(g, orig);

        // Check if possible - distance -1 if not
        if (iNode->getPath() == nullptr){ // include node
            return {path, -1};
        }

        // Get path from node to be included to origin - not including node to include again
        cn = g->findNode(iNode);
        cn = cn->getPath();
        while (cn){
            path.push_back(cn->getId());
            cn = cn->getPath();
        }
        reverse(path.begin(), path.end());

        // Return result
        return {path, dest->getDistance()};
    }
}

// Calculate main environmental route
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<bool, bool>> Route::mainEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
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
        GetDriving gd; // ger driving
        gd.dijkstra(g, orig);

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
        GetWalking gw; // get walking 
        gw.dijkstra(g, n);

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


// Calculate environmental route with no walking limit
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> Route::nwlEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){

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
        GetDriving gd; // get driving
        gd.dijkstra(g, orig);

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
        GetWalking gw; // get walking
        gw.dijkstra(g, n);

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

        // check if current node is a parking node
        if (n->getParking() == 1){

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

// Calculate environmental route with any parking option
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> Route::apoEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){

    // Remove nodes to be avoided
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges to be avoided
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
        GetDriving gd; // get driving
        gd.dijkstra(g, orig);

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
        GetWalking gw; // get walking
        gw.dijkstra(g, n);

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

        // check if current walking time is less the maximum walking time
        if (cwt < mwt){

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

// Calculate environmental route with no rules
pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> Route::nrEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
    // Remove nodes to be avoided
    for (int id : aNodes){ // avoid nodes
        g->removeNode(id);
    }

    // Remove edges to be avoided
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
        GetDriving gd; // get driving
        gd.dijkstra(g, orig);

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
        GetWalking gw; // get walking
        gw.dijkstra(g, n);

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

    // Return result - first best routes and times, second best routes and times
    return {{{fbdr, fbwr}, {fbdt, fbwt}}, {{sbdr, sbwr}, {sbdt, sbwt}}};
}


