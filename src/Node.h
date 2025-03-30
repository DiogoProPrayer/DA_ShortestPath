#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <limits>
#include <vector>
#include <string>
#include <utility>

class Node {
protected:
    std::string location;
    std::string code;
    int id;
    bool parking = false;

    bool visited = false;
    
    double dist = std::numeric_limits<double>::max();
    int pred = -1;
    
    double walking_dist = std::numeric_limits<double>::max();
    int walking_pred = -1;
    bool walking_visited = false;

    std::vector<Edge *> adj;
    std::vector<Edge *> incoming;

    /**
    * @brief Helper to delete an edge from the destination's incoming list
    * @param edge Pointer to the edge to be deleted
    */
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
    /**
     * @brief Node constructor
     * @param Location The location of the node
     * @param id The ID of the node
     * @param Code The code of the node
     * @param Parking Say whether one can park
     */
    Node(std::string Location, int id, std::string Code, bool Parking)
        : location(std::move(Location)), code(std::move(Code)), id(id), parking(Parking) {}

    std::string getLocation() const { return location; }
    std::string getCode() const { return code; }
    int getId() const { return id; }
    bool getParking() const { return parking; }

   
    bool isVisited() const { return visited; }
    double getDist() const { return dist; }
    int getPred() const { return pred; }
    double getWalkingDist() const { return walking_dist; }
    int getWalkingPred() const { return walking_pred; }
    bool getWalkingVisited() const { return walking_visited; }
    std::vector<Edge *> getAdj() const { return adj; }
    bool isEdgeVisited(Node *dest) {
        for (Edge *edge : adj) {
            if (edge->getDest() == dest) {
                return edge->getVisited();
            }
        }
        return false;
    }

    void setVisited(bool visited) { this->visited = visited; }
    void setDist(double dist) { this->dist = dist; }
    void setPred(int p) { this->pred = p; }
    void setWalkingDist(double dist) { this->walking_dist = dist; }
    void setWalkingPred(int pred) { this->walking_pred = pred; }
    void setWalkingVisited(bool visited) { this->walking_visited = visited; }
    void setParking(bool parking) { this->parking = parking; }
    void setEdgeVisited(Node *dest, bool visit) {
        for (Edge *edge : adj) {
            if (edge->getDest() == dest) {
                edge->setVisited(visit);
                return;
            }
        }
    }

    /**
     * @brief Add an edge from this node to a destination node
     * @param dest Pointer to the destination node
     * @param driving Driving time for the edge
     * @param walking Walking time for the edge
     * @return Pointer to the created Edge
     */
    Edge* addEdge(Node *dest, double driving, double walking) {
        auto newEdge = new Edge(this, dest, driving, walking);
        adj.push_back(newEdge);
        dest->incoming.push_back(newEdge);
        return newEdge;
    }

    /**
     * @brief Reset dynamic attributes to default values.
     */
    void resetNode() {
        visited = false;
        dist = std::numeric_limits<double>::max();
        pred = -1;
        walking_dist = std::numeric_limits<double>::max();
        walking_pred = -1;
        walking_visited = false;
    }
};

#endif // NODE_H
