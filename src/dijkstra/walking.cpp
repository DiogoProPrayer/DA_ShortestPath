#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include "graph.h"
#include "walking.h"

using namespace std;

// Helper function to dijkstra algorithm
bool Walking::check(Edge *e) { 
  Node *on = e->getOrig(); // origin node
  Node *dn = e->getDest(); // destination node
  double wt = e->getWalkingTime(); // walking time

  // Check if it's a shorter path
  if (on->getDistance() + wt < dn->getDistance()) {
    dn->setDistance(on->getDistance() + wt); 
    dn->setPath(e);
    return true;
  }
  return false;
}



// Dijkstra algorithm
void Walking::dijkstra(Graph* g, Node* orig) {
  auto ns = g->getNodes(); // nodes

  // Reset all
  for (auto n : ns){ // node
    n->setDistance(INT_MAX);
    n->setPath(nullptr);
  }

  // Start calculating the distance
  orig->setDistance(0); // origin
  MutablePriorityQueue<Node> pq; // priority queue
  pq.insert(orig);
  while (!pq.empty()) {
    Node *cn = pq.extractMin(); // current node

    // Check possible paths
    for (auto &e : cn->getAdj()){ // edge
      Node *nn = e->getDest(); // next node
      if (check(e)){
        pq.insert(nn);
      }
    }
  }
}

