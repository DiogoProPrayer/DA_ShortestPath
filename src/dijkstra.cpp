#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "dijkstra.h"

using namespace std;


// Helper function
bool Dijkstra::check(Edge *edge, bool driving) {
  Node *origNode = edge->getOrig();
  Node *destNode = edge->getDest();


  // If driving
  if (driving) {
    double driveTime = edge->getDrivingTime();

    // You can't drive
    if (driveTime == X){
      return false;
    }

    // If it's a shorter path - update
    if (origNode->getDistance() + driveTime < destNode->getDistance()) {
      destNode->setDistance(origNode->getDistance() + driveTime);
      destNode->setPath(edge);
      return true;
    }
    return false;
  }


  // If walking
  else {
    double walkTime = edge->getWalkingTime();

    // If it's a shorter path - update
    if (origNode->getDistance() + walkTime < destNode->getDistance()) {
      destNode->setDistance(origNode->getDistance() + walkTime);
      destNode->setPath(edge);
      return true;
    }
    return false;
  }
}


// Dijkstra algorithm
void Dijkstra::dijkstra(Graph* graph, Node* orig, bool driving) {
  auto nodes = graph->getNodes();

  // Reset all
  for (auto node : nodes){
    node->setDistance(INT_MAX);
    node->setPath(nullptr);
  }


  // Start calculating the distance
  orig->setDistance(0);
  MutablePriorityQueue<Node> queue;
  queue.insert(orig);
  while (!queue.empty()) {
    Node *currentNode = queue.extractMin();

    // Check possible paths
    for (auto &edge : currentNode->getAdj()){
      Node *nextNode = edge.getDest();
      if (check(&edge, driving)){
        queue.insert(nextNode);
      }
    }
  }
}

