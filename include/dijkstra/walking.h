#ifndef WALKING_H
#define WALKING_H

#include "graph.h"

using namespace std;

// Class to get walking time
class Walking {
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e);

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig);
};

#endif