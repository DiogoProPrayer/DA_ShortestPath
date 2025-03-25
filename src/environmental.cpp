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
pair<BestRoute, bool> Environmental::bestRoute(Graph* graph, Node* orig, Node* dest, int maxWalkingTime, vector<int> avoidNodes, vector<pair<Node*, Node*>> avoidEdges){
    BestRoute bestRoute;
    bool park = false;

    // Remove what can't be used
    for (int id : avoidNodes){
        graph->removeNode(id);
    }
    for (auto& edge : avoidEdges){
        graph->removeEdge(edge.first, edge.second);
    }


    // Get parking nodes - check if none
    vector<Node*> parkingNodes;
    for (Node* node : graph->getNodes()){
      if (node->getParking() == 1){
        parkingNodes.push_back(node);
        park = true;
      }
    }
    if (!park){
      return {bestRoute, park};
    }


    // Go through all parking nodes - return result
    for (Node* node : parkingNodes){
        vector<int> walkPath;
        vector<int> drivePath;
        int walkTime;
        int driveTime;


        // Get walking time - check if possible
        Dijkstra getWalking;
        getWalking.dijkstra(graph, node, false);
        if (dest->getPath() == nullptr || dest->getDistance() > maxWalkingTime){
            continue;
        }

        // Get walking path and distance
        currentNode = graph->findNode(dest);
        while (currentNode){
            walkPath.push_back(currentNode->getId());
            currentNode = currentNode->getPath();
        }
        reverse(walkPath.begin(), walkPath.end());
        walkTime = dest->getDistance();


        // Get driving time - check if possible
        pair<vector<int>, int> drivingRoute = Driving::indRoute(graph, orig, node, true);
        if (drivingRoute.second == -1){
            continue;
        }

        // Get driving path and distance
        drivePath = drivingRoute.first;
        driveTime = drivingRoute.second;


        // Check if better
        int currentTime = driveTime + walkTime;
        int bestTime = bestRoute.driveTime + bestRoute.walkTime;
        if ((currentTime < bestTime) || (currentTime == bestTime && walkTime > bestRoute.walkTime)){
            bestRoute.driveTime = driveTime;
            bestRoute.walkTime = walkTime;
            bestRoute.drivePath = drivePath;
            bestRoute.walkPath = walkPath;
        }
    }
    return {bestRoute, park};
}


// Calculate aproximate environmental route
pair<BestRoute, AltRoute> Environmental::aprRoute(Graph* graph, Node* orig, Node* dest, vector<int> avoidNodes, vector<pair<Node*, Node*>> avoidEdges){
    BestRoute bestRoute;
    AltRoute altRoute;

    // Remove what can't be used
    for (int id : avoidNodes){
        graph->removeNode(id);
    }
    for (auto& edge : avoidEdges){
        graph->removeEdge(edge.first, edge.second);
    }


    // Get parking nodes
    vector<Node*> parkingNodes;
    for (Node* node : graph->getNodes()){
        if (node->getParking() == 1){
            parkingNodes.push_back(node);
        }
    }


    // Go through all parking nodes - return result
    for (Node* node : parkingNodes){
        vector<int> walkPath;
        vector<int> drivePath;
        int walkTime;
        int driveTime;


        // Get walking time - check if possible
        Dijkstra getWalking;
        getWalking.dijkstra(graph, node, false);
        if (dest->getPath() == nullptr){
            continue;
        }

        // Get walking path and distance
        currentNode = graph->findNode(dest);
        while (currentNode){
            walkPath.push_back(currentNode->getId());
            currentNode = currentNode->getPath();
        }
        reverse(walkPath.begin(), walkPath.end());
        walkTime = dest->getDistance();


        // Get driving time - check if possible
        pair<vector<int>, int> drivingRoute = Driving::indRoute(graph, orig, node, true);
        if (drivingRoute.second == -1){
            continue;
        }

        // Get driving path and distance
        drivePath = drivingRoute.first;
        driveTime = drivingRoute.second;


        // Check if better
        int currentTime = driveTime + walkTime;
        int bestTime = bestRoute.driveTime + bestRoute.walkTime;
        int altTime = altRoute.driveTime + altRoute.walkTime;
        if ((currentTime < bestTime) || (currentTime == bestTime && walkTime > bestRoute.walkTime)){
            altRoute.driveTime = bestRoute.driveTime;
            altRoute.walkTime = bestRoute.walkTime;
            altRoute.drivePath = bestRoute.drivePath;
            altRoute.walkPath = bestRoute.walkPath;
            bestRoute.driveTime = driveTime;
            bestRoute.walkTime = walkTime;
            bestRoute.drivePath = drivePath;
            bestRoute.walkPath = walkPath;
        }
        else if ((currentTime < altTime) || (currentTime == altTime && walkTime > altRoute.walkTime)){
            altRoute.driveTime = driveTime;
            altRoute.walkTime = walkTime;
            altRoute.drivePath = drivePath;
            altRoute.walkPath = walkPath;
        }
    }
    return {bestRoute, altRoute};
}

