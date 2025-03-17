#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include "graph.h"
#include "node.h"
#include "edge.h"

using namespace std;

// Define the input X as a -1
#define X -1

// Class to get time
class Dijkstra {
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e, bool driving);
      

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig, bool driving);
};

#endif
