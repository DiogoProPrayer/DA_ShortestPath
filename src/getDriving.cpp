#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"

using namespace std;

#define X -1

class GetDriving {
  private:
    bool check(Edge *e) { 
      Node *v1 = e->getOrig();
      Node *v2 = e->getDest();
      double dt = e->getDrivingTime();
      
      if (dt == X){
        return false;
      }

      if (v1->getDistance() + dt < v2->getDistance()) {
        v2->setDistance(v1->getDistance() + dt);
        v2->setPath(e);
        return true;
      }
      return false;
    }

  public:
    void dijkstra(Graph* g, Node* orig) {
      auto ns = g->getNodes();

      for (auto n : ns){
        n->setDistance(INT_MAX);
        n->setPath(nullptr);
      }

      orig->setDistance(0);
      MutablePriorityQueue<Node> pq;
      pq.insert(orig);
      while (!pq.empty()) {
        Node *cn = pq.extractMin();

        for (auto &e : cn->getAdj()){
          Node *nn = e.getDest();
          if (check(&e)){
            pq.insert(nn);
          }
        }
      }
    }
}
