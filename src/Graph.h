#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include "Node.h"
#include <iostream>

class Graph {
public:

    /**
    * @brief Destructor for the Graph class
    */
    ~Graph();

    /**
     * @brief Finds the index of a node with the ID
     * @param id The ID of the node
     * @return The index of the node if found, -1 otherwise
     */
    int findNodeIndex(const int id) const;

    /**
     * @brief Finds the node in the graph
     * @param in The node to find
     * @return The pointer to the node in the graph
     */
    Node* findNode(const Node &in) const;

    /**
     * @brief Finds a node in the graph by its code
     * @param code The code string of the node
     * @return Pointer to the node of the graph
     */
    Node* findNodeByCode(const std::string &code) const;

    /**
     * @brief Adds a new node to the graph
     * @param in The node to be added
     * @return True if possible, false otherwise
     */
    bool addNode(const Node &in);

    /**
     * @brief Adds a directed edge with times
     * @param source The source Node
     * @param dest The destination Node
     * @param driving Driving time between the nodes
     * @param walking Walking time between the nodes
     * @return True if possible, false otherwise
     */
    bool addEdge(const Node &source, const Node &dest, double driving, double walking) const;

    /**
     * @brief Adds bidirectional edges with times
     * @param source The source Node
     * @param dest The destination Node
     * @param driving Driving time for each direction
     * @param walking Walking time for each direction
     * @return True if possible, false otherwise
     */
    bool addBidirectionalEdge(const Node &source, const Node &dest, double driving, double walking) const;

    /**
     * @brief Gets the total number of vertices in the graph
     * @return The number of nodes in the graph
     */
    int getNumVertex() const;

    /**
     * @brief Gets all nodes in the graph
     * @return A vector of Node pointers
     */
    std::vector<Node *> getNodes() const;

    /**
     * @brief Prints info about each node in the graph
     */
    void printGraph();

    /**
     * @brief Gets the number of nodes in the graph
     * @return The number of nodes in the graph
     */
    int getNodeSize() const;

    /**
     * @brief Gets the node by the index
     * @param idx The position of the node in the graph
     * @return Pointer to the Node
     */
    Node *getNode(int idx) const;

protected:
    std::vector<Node *> Nodes;
    double **distMatrix = nullptr;
    int **pathMatrix = nullptr;
    int findVertexIdx(const Node &in) const;
};

/**
 * @brief Deletes a matrix of integers
 * @param m The matrix to delete
 * @param n The number of rows in the matrix
 */
void deleteMatrix(int **m, int n);

/**
 * @brief Deletes a matrix of doubles
 * @param m The matrix to delete
 * @param n The number of rows in the matrix
 */
void deleteMatrix(double **m, int n);

#endif 