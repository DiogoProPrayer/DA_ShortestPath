#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <limits>
#include <vector>
#include <string>
#include <utility>

class Node {
protected:
    // Static attributes (do not change during algorithm runs)
    std::string location;
    std::string code;
    int id;
    bool parking = false;
    unsigned int indegree;

    // Dynamic attributes (resettable between algorithm runs)
    bool visited = false;
    bool processing = false;
    int low = -1;
    int num = -1;
    
    double dist = std::numeric_limits<double>::max();
    int pred = -1;
    
    double walking_dist = std::numeric_limits<double>::max();
    int walking_pred = -1;
    bool walking_visited = false;
    
    Edge *path = nullptr;
    std::vector<Edge *> adj;
    std::vector<Edge *> incoming;

    // Helper to delete an edge from the destination's incoming list
    void deleteEdge(Edge *edge) {
        Node *dest = edge->getDest();
        auto it = dest->incoming.begin();
        while (it != dest->incoming.end()) {
            if (*it == edge) {
                it = dest->incoming.erase(it);
            } else {
                ++it;
            }
        }
        delete edge;
    }

public:
    // Constructor
    Node(std::string Location, int id, std::string Code, bool Parking)
        : location(std::move(Location)), code(std::move(Code)), id(id), parking(Parking), indegree(0) {}

    // Getters for static attributes
    std::string getLocation() const { return location; }
    std::string getCode() const { return code; }
    int getId() const { return id; }
    bool getParking() const { return parking; }
    unsigned int getIndegree() const { return indegree; }

    // Getters for dynamic attributes
    bool isVisited() const { return visited; }
    bool isProcessing() const { return processing; }
    int getLow() const { return low; }
    int getNum() const { return num; }
    double getDist() const { return dist; }
    int getPred() const { return pred; }
    double getWalkingDist() const { return walking_dist; }
    int getWalkingPred() const { return walking_pred; }
    bool getWalkingVisited() const { return walking_visited; }
    Edge* getPath() const { return path; }
    std::vector<Edge *> getAdj() const { return adj; }

    // Setter methods for dynamic attributes
    void setVisited(bool visited) { this->visited = visited; }
    void setProcessing(bool processing) { this->processing = processing; }
    void setLow(int value) { this->low = value; }
    void setNum(int value) { this->num = value; }
    void setIndegree(unsigned int inDegree) { this->indegree = inDegree; }
    void setDist(double dist) { this->dist = dist; }
    void setPred(int p) { this->pred = p; }
    void setPath(Edge *path) { this->path = path; }
    void setWalkingDist(double dist) { this->walking_dist = dist; }
    void setWalkingPred(int pred) { this->walking_pred = pred; }
    void setWalkingVisited(bool visited) { this->walking_visited = visited; }

    // Other member functions
    bool isEdgeVisited(Node *dest) {
        for (Edge *edge : adj) {
            if (edge->getDest() == dest) {
                return edge->getVisited();
            }
        }
        return false;
    }

    void setEdgeVisited(Node *dest, bool visit) {
        for (Edge *edge : adj) {
            if (edge->getDest() == dest) {
                edge->setVisited(visit);
                return;
            }
        }
    }

    // Add an edge from this node to a destination node
    Edge* addEdge(Node *dest, double driving, double walking) {
        auto newEdge = new Edge(this, dest, driving, walking);
        adj.push_back(newEdge);
        dest->incoming.push_back(newEdge);
        return newEdge;
    }

    // Remove edges going from this node to node n
    bool removeEdge(Node *n) {
        bool removedEdge = false;
        auto it = adj.begin();
        while (it != adj.end()) {
            Edge *edge = *it;
            Node *org = edge->getOrig();
            if (org == n) {  // Compare node pointers
                it = adj.erase(it);
                deleteEdge(edge);
                removedEdge = true;
            } else {
                ++it;
            }
        }
        return removedEdge;
    }

    // Remove all outgoing edges from this node
    void removeOutgoingEdges() {
        auto it = adj.begin();
        while (it != adj.end()) {
            Edge *edge = *it;
            it = adj.erase(it);
            deleteEdge(edge);
        }
    }

    // Reset dynamic attributes to default values.
    void resetNode() {
        visited = false;
        processing = false;
        low = -1;
        num = -1;
        dist = std::numeric_limits<double>::max();
        pred = -1;
        walking_dist = std::numeric_limits<double>::max();
        walking_pred = -1;
        walking_visited = false;
        path = nullptr;
    }
};

#endif // NODE_H
