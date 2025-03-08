#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"

using namespace std;

// Define the input X as a -1
#define X -1

// Class to get driving time
class GetDriving {
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e) {  // edge
      Node *on = e->getOrig(); // origin node
      Node *dn = e->getDest(); // destination node
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
      return false;
    }

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig) {
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
          Node *nn = e.getDest(); // next node
          if (check(&e)){
            pq.insert(nn);
          }
        }
      }
    }
}
