//
// Created by buttercup on 17-03-2025.
//

#ifndef EDGE_H
#define EDGE_H

class Node;
class Edge {
protected:
    Node *org;
    Node *dest;
    double drivingTime;
    double walkingTime;
    bool visited = false;

public:

    /**
    * @brief Edge constructor
    * @param org Pointer to the origin Node
    * @param dest Pointer to the destination Node
    * @param driving The driving time for the edge
    * @param walking The walking time for the edge
    */
    Edge(Node *org, Node*dest, double driving, double walking) {
        this->org=org;
        this->dest=dest;
        drivingTime=driving;
        walkingTime=walking;
    }

    // Getters
    Node * getDest() const {
        return dest;
    };
    Node * getOrig() const {
        return org;
    };
    double getDrivingTime() const {
        return drivingTime;
    };
    double getWalkingTime() const {
        return walkingTime;
    };
   bool getVisited() const {
        return visited;
    }
    void setVisited(bool visit) {
        this->visited=visit;
    }
};
#endif //EDGE_H

