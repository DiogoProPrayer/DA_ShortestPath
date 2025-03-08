#ifndef GETWALKING_H
#define GETWALKING_H

#include "graph.h"
#include "node.h"
#include "edge.h"

using namespace std;

// Class to get walking time
class GetWalking {
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e);

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig);
};

#endif