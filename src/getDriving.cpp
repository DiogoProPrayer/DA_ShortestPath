#ifndef GETDRIVING_H
#define GETDRIVING_H

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <graph.h>

using namespace std;

#define X -1

template <class T>
class GetDriving {

  bool check(Edge<T> *e) { 
    Node<T> *v1 = e->getOrig();
    Node<T> *v2 = e->getDest();
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

    orig->setDistance(0);
    MutablePriorityQueue<Vertex<T>> pq;
    pq.insert(orig);
    while (!pq.empty()) {
      Node<T> *cn = pq.extractMin();

      for (auto &e : cn->getAdj()){
        Node<T> *nn = e.getDest();
        if (check(&e){
          pq.insert(nn);
        }
      }
    }
  }
  
}

#endif

