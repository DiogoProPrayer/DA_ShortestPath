#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <graph.h>

using namespace std;

#define X -1

template <class T>
class RouteDriving {
  bool relax(Edge<T> *e) { 
    Vertex<T> *v1 = e->getOrig();
    Vertex<T> *v2 = e->getDest();
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

  void dijkstra(Graph<T>* g, Node<T>* orig) {
    auto ns = g->getNodes();

    for (auto n : ns){
      n->setDist(INT_MAX);
      n->setPath(nullptr);
    }

    if (!orig) return;

    orig->setDistance(0);
    MutablePriorityQueue<Vertex<T>> pq;
    pq.insert(orig);
    while (!pq.empty()) {
      Node<T> *cn = pq.extractMin();

      for (auto &e : cn->getAdj()){
        Node<T> *nn = e.getDest();
        if (relax(&e){
          pq.insert(nv);
        }
      }
    }
  }
}

#endif