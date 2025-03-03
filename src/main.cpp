#include <iostream>
#include "graph.h"
#include "node.h"
#include "edge.h"
using namespace std;

int main(){
  Graph g;

  Node a("Test1", 1, "p1", false)
  Node b("Test2", 2, "p2", true);

  g.addNode(a);
  g.addNode(b);

  g.addBidirectionalEdge(a, b, 10, 30);

  cout << g.getNumVertexes() << endl;

  return 0;
}

