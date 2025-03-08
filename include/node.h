#ifndef NODE_H
#define NODE_H

#include <string>
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
        Node(string location, int id, string code, bool parking);

        // Getters
        string getLocation() const;
        int getId() const;
        string getCode() const;
        bool getParking() const;
        bool isVisited() const;
        double getDistance() const;
        int getInDegree() const;
        bool isProcessing() const;
        int getLow() const;
        int getNum() const;
        vector<Edge *> getAdj() const;
        Edge *getPath() const;

        // Setters
        void setVisited(bool visited);
        void setDistance(double ditance);
        void setInDegree(unsigned int inDegree);
        void setProcessing(bool processing);
        void setLow(int value);
        void setNum(int value);
        void setPath(Edge *path);

        // Functions
        // Add edge
        Edge* addEdge(Node *dest, double drivingTime, double walkingTime);
        // Remove outgoing edges
        void removeOutgoingEdges();

        // Delete edge
        void deleteEdge(Edge *edge);

        // Remove edge
        bool removeEdge(Node *n);
};

#endif