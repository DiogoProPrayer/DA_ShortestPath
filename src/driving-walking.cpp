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
    priority_queue<Node *> pq;
    vector<Node *> parkingNodes;
    pq.push(graph.getNode(source));
    cout<<pq.top()->getId()<<endl;
    cout<<source<<endl;
    
    return parkingNodes;
}


bool DrivingWalking::calculateRoute()
{
    // Search shortest paths to the nodes with parking spots that are inside the walking time limit
    vector<Node *> parkingNodes = walking_to_parks();
    // Search the shortest paths that connect to those parking spots

    return false;
}