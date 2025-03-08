#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <utility>
#include <vector>
#include "node.h"
#include "edge.h"

using namespace std;

// Class graph
class Graph {
    protected:

        // Data
        vector<Node *> Nodes;
        double ** distMatrix = nullptr;
        int **pathMatrix = nullptr;
    public:

        // Destructor
        ~Graph();

        // Getters
        int getNumVertex() const;

        vector<Node *> getNodes() const;

        // Functions
        // Find node index
        int findNodeIndex(const Node &in) const;

        // Find node
        Node *findNode(const Node &in) const;

        // Add node
        bool addNode(const Node &in);

        // Remove node
        bool removeNode(const int in);

        // Add edge
        bool addEdge(const Node &orig, const Node &dest, double drivingTime, double walkingTime);

        // Remove edge
        bool removeEdge(const Node &orig, const Node &dest);

        // Add bidirectional edge
        bool addBidirectionalEdge(const Node &orig, const Node &dest, double drivingTime, double walkingTime);

        // Find vertex index
        int findVertexIdx(const Node &in) const;

        // Delete matrix
        void deleteMatrix(int **m, int n);

        // Delete matrix
        void deleteMatrix(double **m, int n);
};

#endif