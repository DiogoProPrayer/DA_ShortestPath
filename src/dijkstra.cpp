#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include "graph.h"
<<<<<<<< HEAD:src/dijkstra/driving.cpp
#include "driving.h"
========
#include "node.h"
#include "edge.h"
#include "dijkstra.h"
>>>>>>>> environmental:src/dijkstra.cpp

using namespace std;

// Helper function to dijkstra algorithm
<<<<<<<< HEAD:src/dijkstra/driving.cpp
bool Driving::check(Edge *e) {  // edge
  Node *on = e->getOrig(); // origin node
  Node *dn = e->getDest(); // destination node
  double dt = e->getDrivingTime(); // driving time
  // You can't drive
  if (dt == X){
========
bool Dijkstra::check(Edge *e, bool driving) {  // edge
  Node *on = e->getOrig(); // origin node
  Node *dn = e->getDest(); // destination node

  if (driving) {
    double dt = e->getDrivingTime(); // driving time

    // You can't drive
    if (dt == X){
      return false;
    }

    // If it's a shorter path - update
    if (on->getDistance() + dt < dn->getDistance()) {
      dn->setDistance(on->getDistance() + dt);
      dn->setPath(e);
      return true;
    }
>>>>>>>> environmental:src/dijkstra.cpp
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
<<<<<<<< HEAD:src/dijkstra/driving.cpp
void Driving::dijkstra(Graph* g, Node* orig) {
========
void GetDriving::dijkstra(Graph* g, Node* orig, bool driving) {
>>>>>>>> environmental:src/dijkstra.cpp
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
<<<<<<<< HEAD:src/dijkstra/driving.cpp
      Node *nn = e->getDest(); // next node
      if (check(e)){
========
      Node *nn = e.getDest(); // next node
      if (check(&e, driving)){
>>>>>>>> environmental:src/dijkstra.cpp
        pq.insert(nn);
      }
    }
  }
}

