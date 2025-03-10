#ifndef DRIVING_H
#define DRIVING_H

#include "../structs/graph.h"
#include "driving.h"

using namespace std;

// Define the input X as a -1
#define X -1

// Class to get driving time
class Driving {
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e);
      

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig);
};

#endif
