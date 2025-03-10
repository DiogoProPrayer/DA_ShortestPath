#include "node.h"
#include "edge.h"

using namespace std;

// Constructor
Edge::Edge(Node *orig, Node* dest, double drivingTime, double walkingTime) {
    this->orig = orig;
    this->dest = dest;
    this->drivingTime = drivingTime;
    this->walkingTime = walkingTime;
    flow = 0;
}

// Getters
Node * Edge::getDest() const {
    return dest;
}
Node * Edge::getOrig() const {
    return orig;
}
bool Edge::isSelected() const {
    return selected;
}
double Edge::getDrivingTime() const {
    return drivingTime;
}
double Edge::getWalkingTime() const {
    return walkingTime;
}
Edge* Edge::getReverse() const {
    return reverse;
}
double Edge::getFlow() const {
    return flow;
}

// Setters
void Edge::setSelected(bool selected) {
    this->selected = selected;
}
void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}
void Edge::setFlow(double flow) {
    this->flow = flow;
}
