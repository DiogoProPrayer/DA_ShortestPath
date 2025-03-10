#include <string>
#include <utility>
#include <vector>
#include "node.h"
#include "edge.h"

using namespace std;

// Constructor
Node::Node(string location, int id, string code, bool parking) {
    this->location = move(location);
    this->id = id;
    this->code = move(code);
    this->parking = parking;
}

// Getters
string Node::getLocation() const {
    return location;
}
int Node::getId() const {
    return id;
}
string Node::getCode() const {
    return code;
}
bool Node::getParking() const {
    return parking;
}
bool Node::isVisited() const {
    return visited;
}
double Node::getDistance() const {
    return distance;
}
int Node::getInDegree() const {
    return inDegree;
}
bool Node::isProcessing() const {
    return processing;
}
int Node::getLow() const {
    return low;
}
int Node::getNum() const {
    return num;
}
vector<Edge *> Node::getAdj() const {
    return adj;
}
Edge* Node::getPath() const {
    return path;
}

// Setters
void Node::setVisited(bool visited) {
    this->visited = visited;
}
void Node::setDistance(double ditance) {
    this->distance = distance;
}
void Node::setInDegree(unsigned int inDegree) {
    this->inDegree = inDegree;
}
void Node::setProcessing(bool processing) {
    this->processing = processing;
}
void Node::setLow(int value) {
    this->low = value;
}
void Node::setNum(int value) {
    this->num = value;
}
void Node::setPath(Edge *path) {
    this->path = path;
}

// Functions
// Add edge
Edge* Node::addEdge(Node *dest, double drivingTime, double walkingTime) {
    auto newEdge = new Edge(this, dest, drivingTime, walkingTime);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

// Remove outgoing edges
void Node::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

// Delete edge
void Node::deleteEdge(Edge *edge) {
    Node *dest = edge->getDest();

    // Remove from the destination's incoming edges
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

// Remove edge
bool Node::removeEdge(Node *n) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        if (edge->getDest() == n) {  // Compare edge pointers, not the nodes
            it = adj.erase(it);  // Remove edge from adjacency list
            deleteEdge(edge);  // Handle additional cleanup
            removedEdge = true;
        } else {
            ++it;
        }
    }
    return removedEdge;
}
