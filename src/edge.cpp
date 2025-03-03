//
// Created by cisco on 03/03/2025.
//

#include "edge.h"
#include <string>
#include <utility>
#include <vector>
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
    Edge(Node *orig, Node* dest, double drivingTime, double walkingTime) {
        this->orig = orig;
        this->dest = dest;
        this->drivingTime = drivingTime;
        this->walkingTime = walkingTime;
        flow = 0;
    }

    // Getters
    Node * getDest() const {
        return dest;
    }
    Node * getOrig() const {
        return orig;
    }
    bool isSelected() const {
        return selected;
    }
    double getDrivingTime() const {
        return drivingTime;
    }
    double getWalkingTime() const {
        return walkingTime;
    }
    Edge *getReverse() const {
        return reverse;
    }
    double getFlow() const {
        return flow;
    }

    // Setters
    void setSelected(bool selected) {
        this->selected = selected;
    }
    void setReverse(Edge *reverse) {
        this->reverse = reverse;
    }
    void setFlow(double flow) {
        this->flow = flow;
    }
};