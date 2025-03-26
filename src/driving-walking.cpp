#include "driving-walking.h"
#include <queue>
#include <algorithm>
using namespace std;


DrivingWalking::DrivingWalking(Graph graph, int source, int destination, int maxWalkTime, unordered_set<int> avoidNodes, unordered_set<pair<int, int>, pair_hash> avoidSegments)
{
    this->graph = graph;
    this->source = source;
    this->destination = destination;
    this->maxWalkTime = maxWalkTime;
    this->avoidNodes = avoidNodes;
    this->avoidSegments = avoidSegments;
}

unordered_set<Node *> DrivingWalking::walking_to_parks()
{
    priority_queue<Node *, vector<Node*>, CompareNodeWalking> pq;
    unordered_set<Node *> parkingNodes;

    Node *sourceNode = graph.getNode(destination);
    sourceNode->setWalkingDist(0);
    sourceNode->setWalkingPred(-1);
    pq.push(sourceNode);

    while (!pq.empty()) 
    {
        Node *current = pq.top();
        pq.pop();

        // If the node has already been visited, skip it
        if (current->getWalkingVisited()) 
        {
            continue;
        }

        // Stop processing if the walking distance exceeds maxWalkTime
        if (current->getWalkingDist() > maxWalkTime)
        {
            break;
        }

        current->setWalkingVisited(true);

        // If it's a parking node, store it
        if (current->getParking())
        {
            parkingNodes.emplace(current);
        }

        // Process adjacent nodes
        for (auto edge : current->getAdj())
        {
            Node *dest = edge->getDest();

            // Skip if the segment should be avoided or if the destination node is in the avoid list
            if (avoidSegments.find({current->getId(), dest->getId()}) != avoidSegments.end() ||
            avoidNodes.find(dest->getId()) != avoidNodes.end() || avoidSegments.find({dest->getId(), current->getId()}) != avoidSegments.end())
            {
                continue;
            }

            double newDist = current->getWalkingDist() + edge->getWalkingTime();

            // Ensure the new distance is better and within maxWalkTime
            if (newDist < dest->getWalkingDist() && newDist <= maxWalkTime)
            {
                dest->setWalkingDist(newDist);
                dest->setWalkingPred(current->getId());
                pq.push(dest);
            }
        }
    }

    return parkingNodes;
}



bool DrivingWalking::driving_to_parks(unordered_set<Node *> parkingNodes)
{
    priority_queue<Node *, vector<Node*>, CompareNodeDriving> pq;
    Node *sourceNode = graph.getNode(source);
    sourceNode->setDist(0);
    sourceNode->setPred(-1);
    pq.push(sourceNode);

    Node *nodeWithshortestPath = nullptr;

    while (!pq.empty())
    {
        Node *current = pq.top();
        pq.pop();

        if (current->isVisited()) 
        {
            continue;
        }

        current->setVisited(true);

        // If current node is a parking node and is in the set of valid parking nodes
        if (current->getParking() && parkingNodes.find(current) != parkingNodes.end())
        {
            double totalTime = current->getDist() + current->getWalkingDist();

            if (nodeWithshortestPath == nullptr || 
                totalTime < (nodeWithshortestPath->getDist() + nodeWithshortestPath->getWalkingDist()) ||
                (totalTime == (nodeWithshortestPath->getDist() + nodeWithshortestPath->getWalkingDist()) &&
                 current->getWalkingDist() > nodeWithshortestPath->getWalkingDist())) 
            {
                nodeWithshortestPath = current;
            }
        }

        for (auto edge : current->getAdj())
        {
            Node *dest = edge->getDest();

            if (avoidSegments.find({current->getId(), dest->getId()}) != avoidSegments.end() ||
                avoidNodes.find(dest->getId()) != avoidNodes.end() || avoidSegments.find({dest->getId(), current->getId()}) != avoidSegments.end())
            {
                continue;
            }

            double newDist = current->getDist() + edge->getDrivingTime();

            if (newDist < dest->getDist())
            {
                dest->setDist(newDist);
                dest->setPred(current->getId());
                pq.push(dest);
            }
        }
    }

    if (nodeWithshortestPath == nullptr){
        return false;
    }

    // Clear previous results
    result.driving_route.clear();
    result.walking_route.clear();

    int node = nodeWithshortestPath->getId();
    // Store driving path
    while(node != -1)
    {
        result.driving_route.push_back(node);
        node = graph.getNode(node)->getPred();
    }
    reverse(result.driving_route.begin(), result.driving_route.end());
    // Store walking path
    node = nodeWithshortestPath->getWalkingPred();
    result.walking_route.push_back(nodeWithshortestPath->getId());
    while (node != -1)
    {
        result.walking_route.push_back(node);
        node = graph.getNode(node)->getWalkingPred();
    }

    result.driving_time = nodeWithshortestPath->getDist();
    result.walking_time = nodeWithshortestPath->getWalkingDist();
    result.parking_node = nodeWithshortestPath->getId();

    return true;
}




DrivingWalkingResult DrivingWalking::calculateRoute()
{
    result.no_parking = true;
    for(auto node : graph.getNodes())
    {
        node->resetNode();

        if(node->getParking()){
            result.no_parking = false;
            break;
        }
    }
    if(result.no_parking) {return result;}


    unordered_set<Node *> parkingNodes = walking_to_parks();

    // Search the shortest paths that connect to those parking spots
    if(parkingNodes.empty()){ 
        result.no_range = true;
        return result;
    }

    if(!driving_to_parks(parkingNodes))
    {
        result.no_range = true;
        return result;
    }

    return result;
}

pair<DrivingWalkingResult, DrivingWalkingResult> DrivingWalking::alternativeRoutes()
{
    this->maxWalkTime = numeric_limits<int>::max();
    this->result = calculateRoute();

    if(result.no_parking || result.no_range)
    {
        return {result, result};
    }

    for(auto node : graph.getNodes())
    {
        node->resetNode();
    }

    avoidNodes.insert(result.parking_node);

    DrivingWalkingResult alternative1 = calculateRoute();
    if(alternative1.no_parking || alternative1.no_range)
    {
        return {result, alternative1};
    }

    return {result, alternative1};
}