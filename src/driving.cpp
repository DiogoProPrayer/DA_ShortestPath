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
pair<vector<int>, int> Driving::indRoute(Graph* graph, Node* orig, Node* dest, bool best){


  	// Best route
  	vector<int> path;

    // Get driving time - check if possible
    Dijkstra getDriving;
    getDriving.dijkstra(graph, orig, true);
    if (dest->getPath() == nullptr || dest->getParking() == 0){
        return {path, -1};
    }

    // Get path - return
    Node *currentNode = graph->findNode(dest);
    while (currentNode){
        path.push_back(currentNode->getId());
        currentNode = currentNode->getPath();
    }
    reverse(path.begin(), path.end());
    if (best) {
        return {path, dest->getDistance()};
    }


    // Alternative route
    vector<int> altPath;

    // Remove nodes used in best route
    for (int i = 1; i < path.size()-1; i++){
        graph->removeNode(path[i]);
    }

    // Get driving time - check if possible
    getDriving.dijkstra(graph, orig, true);
    if (dest->getPath() == nullptr || dest->getParking() == 0){
        return {altPath, -1};
    }

    // Get path - return
    currentNode = graph->findNode(dest);
    while (currentNode){
        altPath.push_back(currentNode->getId());
        currentNode = currentNode->getPath();
    }
    reverse(altPath.begin(), altPath.end());
    return {altPath, dest->getDistance()};
}


// Calculate restricted driving route
pair<vector<int>, int> Driving::resRoute(Graph* graph, Node* orig, Node* dest, vector<int> avoidNodes, vector<pair<Node*, Node*>> avoidEdges, Node* includeNode){

    // Remove what can't be used
    for (int id : avoidNodes){
        graph->removeNode(id);
    }
    for (auto& edge : avoidEdges){
        graph->removeEdge(edge.first, edge.second);
    }


    // If no node to include
    if (includeNode == nullptr) {
        return indRoute(graph, orig, dest, true)
    }


    // If node to include
    else {
        vector<int> path;
        int dist = 0;


        // Get driving time from node to include - check if possible
        Dijkstra getDriving;
        getDriving.dijkstra(graph, includeNode, true);
        if (dest->getPath() == nullptr || dest->getParking() == 0){
            return {path, -1};
        }

        // Get path and distance from destination to node to include
        Node *currentNode = graph->findNode(dest);
        while (currentNode){
            path.push_back(currentNode->getId());
            currentNode = currentNode->getPath();
        }
        dist += dest->getDistance();


        // Get driving time from origin - check if possible
        getDriving.dijkstra(graph, orig);
        if (includeNode->getPath() == nullptr){
            return {path, -1};
        }

        // Get path and distance from node to be included to origin
        currentNode = graph->findNode(includeNode);
        currentNode = currentNode->getPath();
        while (currentNode){
            path.push_back(currentNode->getId());
            currentNode = currentNode->getPath();
        }
        dist += includeNode->getDistance();


        // Return
        reverse(path.begin(), path.end());
        return {path, dist};
    }
}