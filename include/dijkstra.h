<<<<<<<< HEAD:include/dijkstra/driving.h
#ifndef DRIVING_H
#define DRIVING_H
========
#ifndef DJIKSTRA_H
#define DJIKSTRA_H
>>>>>>>> environmental:include/dijkstra.h

#include "../structs/graph.h"
#include "driving.h"

using namespace std;

// Define the input X as a -1
#define X -1

<<<<<<<< HEAD:include/dijkstra/driving.h
// Class to get driving time
class Driving {
========
// Class to get time
class Dijkstra {
>>>>>>>> environmental:include/dijkstra.h
  private:

    // Helper function to dijkstra algorithm
    bool check(Edge *e, bool driving);
      

  public:

    // Dijkstra algorithm
    void dijkstra(Graph* g, Node* orig, bool driving);
};

#endif
