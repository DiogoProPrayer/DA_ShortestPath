#ifndef EDGE_H
#define EDGE_H

#include "node.h"

using namespace std;

// Class edge
class Edge {
protected:

    // Data
    Node *orig;
    Node *dest;
    double drivingTime;
    double walkingTime;
    bool selected = false;
    Edge *reverse = nullptr;
    double flow;
public:

    // Constructor
    Edge(Node *orig, Node* dest, double drivingTime, double walkingTime);

    // Getters
    Node * getDest() const;
    Node * getOrig() const;
    bool isSelected() const;
    double getDrivingTime() const;
    double getWalkingTime() const;
    Edge *getReverse() const;
    double getFlow() const;

    // Setters
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
};

#endif