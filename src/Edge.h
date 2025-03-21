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
    bool selected = false;
    bool visited = false;
    Edge *reverse = nullptr;

    double flow;
public:
    Edge(Node *org,Node*dest, double driving, double walking) {
        this->org=org;
        this->dest=dest;
        drivingTime=driving;
        walkingTime=walking;
    }
    Node * getDest() const {
        return dest;
    };
    Node * getOrig() const {
        return org;
    };
    bool isSelected() const {
        return selected;
    };
    double getDrivingTime() const {
        return drivingTime;
    };
    double getWalkingTime() const {
        return walkingTime;
    };
    Edge *getReverse() const {
        return reverse;
    };
    double getFlow() const {
        return flow;
    };
   bool getVisited() const {
        return visited;
    }
    void setVisited(bool visit) {
        this->visited=visit;
    }

    void setSelected(bool selected) {
        this->selected=selected;
    };
    void setReverse(Edge *reverse) {
        this->reverse=reverse;
    };
    void setFlow(double flow) {
        this->flow=flow;
    };

};
#endif //EDGE_H

