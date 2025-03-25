#include "driving-walking.h"
#include <queue>
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

vector<Node *> DrivingWalking::walking_to_parks()
{
    priority_queue<Node *, vector<Node*>, CompareNodeWalking> pq;
    vector<Node *> parkingNodes;

    Node *sourceNode = graph.getNode(source);
    sourceNode->setWalkingDist(0);
    sourceNode->setWalkingPred(-1);
    pq.push(sourceNode);

    while (!pq.empty()) 
    {
        Node *current = pq.top();
        pq.pop();

        // If the node has already been visited, skip it
        if (current->isVisited()) 
        {
            continue;
        }

        // Stop processing if the walking distance exceeds maxWalkTime
        if (current->getWalkingDist() >= maxWalkTime)
        {
            break;
        }

        current->setVisited(true);

        // If it's a parking node, store it
        if (current->getParking())
        {
            parkingNodes.push_back(current);
        }

        // Process adjacent nodes
        for (auto edge : current->getAdj())
        {
            Node *dest = edge->getDest();

            // Skip if the segment should be avoided or if the destination node is in the avoid list
            if (avoidSegments.find({current->getId(), dest->getId()}) != avoidSegments.end() ||
                avoidNodes.find(dest->getId()) != avoidNodes.end())
            {
                continue;
            }

            double newDist = current->getWalkingDist() + edge->getWalkingTime();

            // Ensure the new distance is better and within maxWalkTime
            if (newDist < dest->getWalkingDist() && newDist < maxWalkTime)
            {
                dest->setWalkingDist(newDist);
                dest->setWalkingPred(current->getId());
                pq.push(dest);
            }
        }
    }

    return parkingNodes;
}

pair<DrivingWalkingResult, DrivingWalkingResult> DrivingWalking::alternativeRoutes()
{
    this->maxWalkTime = numeric_limits<int>::max();
    this->result = calculateRoute();

    

    return {result, alternative1};
}

DrivingWalkingResult DrivingWalking::calculateRoute()
{
    result.no_parking = true;
    for(auto node : graph.getNodes())
    {
        if(node->getParking()){
            result.no_parking = false;
            break;
        }
    }
    if(result.no_parking) {return result;}


    vector<Node *> parkingNodes = walking_to_parks();
    for(auto node : parkingNodes)
    {
        cout << "Parking node: " << node->getId() << " " << node->getLocation() << "   Tempo:"<< node->getWalkingDist() << endl;
    }
    // Search the shortest paths that connect to those parking spots
    if(parkingNodes.empty()){ 
        result.no_range = true;
        return result;
    }

    // Search the shortest paths that connect to those parking spots



    return result;
}