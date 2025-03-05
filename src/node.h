#ifndef NODE_H
#define NODE_H

#include <string>
#include <utility>
#include <vector>
#include "edge.h"
using namespace std;

// Class node
class Node {
    protected:

        // Data
        string location;
        int id;
        string code;
        bool parking;
        bool visited = false;
        double distance = 0;
        int inDegree = 0;
        bool processing = false;
        int low = -1, num = -1;
        vector<Edge *> adj;
        Edge *path = nullptr;
        vector<Edge *> incoming;
    public:

        // Constructor
        Node(string location, int id, string code, bool parking) {
            this->location = move(location);
            this->id = id;
            this->code = move(code);
            this->parking = parking;
        }

        // Getters
        string getLocation() const {
            return location;
        }
        int getId() const {
            return id;
        }
        string getCode() const {
            return code;
        }
        bool getParking() const {
            return parking;
        }
        bool isVisited() const {
            return visited;
        }
        double getDistance() const {
            return distance;
        }
        int getInDegree() const {
            return inDegree;
        }
        bool isProcessing() const {
            return processing;
        }
        int getLow() const {
            return low;
        }
        int getNum() const {
            return num;
        }
        vector<Edge *> getAdj() const {
            return adj;
        }
        Edge *getPath() const {
            return path;
        }

        // Setters
        void setVisited(bool visited) {
            this->visited = visited;
        }
        void setDistance(double ditance) {
            this->distance = distance;
        }
        void setInDegree(unsigned int inDegree) {
            this->inDegree = inDegree;
        }
        void setProcessing(bool processing) {
            this->processing = processing;
        }
        void setLow(int value) {
            this->low = value;
        }
        void setNum(int value) {
            this->num = value;
        }
        void setPath(Edge *path) {
            this->path = path;
        }

        // Functions
        // Add edge
        Edge* addEdge(Node *dest, double drivingTime, double walkingTime) {
            auto newEdge = new Edge(this, dest, drivingTime, walkingTime);
            adj.push_back(newEdge);
            dest->incoming.push_back(newEdge);
            return newEdge;
        }

        // Remove outgoing edges
        void removeOutgoingEdges() {
            auto it = adj.begin();
            while (it != adj.end()) {
                Edge *edge = *it;
                it = adj.erase(it);
                deleteEdge(edge);
            }
        }

        // Delete edge
        void deleteEdge(Edge *edge) {
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
        bool removeEdge(Node *n) {
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
};

#endif