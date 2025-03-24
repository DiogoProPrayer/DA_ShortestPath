#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "dijkstra.h"

using namespace std;

// Helper function to dijkstra algorithm
bool Dijkstra::check(Edge *e, bool driving) {
  Node *on = e->getOrig(); // origin node
  Node *dn = e->getDest(); // destination node

  if (driving) {
    double dt = e->getDrivingTime(); // driving time

    // You can't drive
    if (dt == X) {
      return false;
    }

    // If it's a shorter path - update
    if (on->getDistance() + dt < dn->getDistance()) {
      dn->setDistance(on->getDistance() + dt);
      dn->setPath(e);
      return true;
    }
    return false;
  }
  else {
    double wt = e->getWalkingTime(); // walking time

    // If it's a shorter path - update
    if (on->getDistance() + wt < dn->getDistance()) {
      dn->setDistance(on->getDistance() + wt);
      dn->setPath(e);
      return true;
    }
    return false;
  }
}

// Dijkstra algorithm
void Dijkstra::dijkstra(Graph* g, Node* orig, bool driving) {
  auto ns = g->getNodes(); // nodes

  // Reset all
  for (auto n : ns) { // node
    n->setDistance(INT_MAX);
    n->setPath(nullptr);
  }

  // Start calculating the distance
  orig->setDistance(0); // origin
  // Assuming you have a MutablePriorityQueue class
  // If not, you'll need to implement a priority queue mechanism
  // MutablePriorityQueue<Node> pq;
  // pq.insert(orig);
  
  // Note: The priority queue implementation is not shown here
  // You'll need to replace this with your actual priority queue logic
  
  // Placeholder implementation
  while (!ns.empty()) {
    Node *cn = orig; // current node (this is a placeholder)

    // Check possible paths
    for (auto &e : cn->getAdj()) { // edge
      Node *nn = e->getDest(); // next node
      if (check(e, driving)) {
        // Add appropriate priority queue insertion logic
      }
    }
    break; // Prevent infinite loop (remove in actual implementation)
  }
}