#ifndef GETDRIVING_H
#define GETDRIVING_H

#include "graph.h"
#include "node.h"
#include "edge.h"

using namespace std;

// Define the input X as a -1
#define X -1

// Class to get driving time
class GetDriving {
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e);
      

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig);
};

#endif
