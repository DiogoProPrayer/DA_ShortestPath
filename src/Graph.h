#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include "Node.h"
#include <iostream>

class Graph {
public:
    ~Graph();

    int findNodeIndex(const int id) const;
    Node* findNode(const Node &in) const;
    Node* findNodeByCode(const std::string &code) const;
    bool addNode(const Node &in);
    bool removeNode(const int in);
    bool addEdge(const Node &source, const Node &dest, double driving, double walking) const;
    bool removeEdge(const Node &source, const Node &dest) const;
    bool addBidirectionalEdge(const Node &source, const Node &dest, double driving, double walking) const;
    int getNumVertex() const;
    std::vector<Node *> getNodes() const;
    void printGraph();
    int getNodeSize() const;

protected:
    std::vector<Node *> Nodes;
    double **distMatrix = nullptr;
    int **pathMatrix = nullptr;
    int findVertexIdx(const Node &in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif 