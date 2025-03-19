//
// Created by buttercup on 17-03-2025.
//

#ifndef NODE_H
#define NODE_H
#include "Edge.h"

class Node {
    protected:
        std::string location;
        std::string code;
        int id;
        bool parking;
        bool visited=false;
        unsigned int indegree;
        bool processing = false;
        int low = -1, num = -1;
        double dist = 0;
        int pred;
        std::vector<Edge *> adj;
        Edge *path = nullptr;
        std::vector<Edge *> incoming;

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

    public:
    Node(std::string Location,int id,std::string Code,bool Parking) {
        this->location=std::move(Location);
        this->code=std::move(Code);
        this->parking=Parking;
        this->id=id;
    }
    std::string getLocation() {
        return location;
    };
    std::string getCode() {
        return code;
    };
    int getId() const {return id;}
    bool getParking() const {
        return parking;
    };
    int getPred()const {
        return pred;
    }
    bool isVisited() const {
        return visited;
    };
    bool isEdgeVisited(Node *dest) {
        for (Edge *edge : adj) {
            if (edge->getDest() == dest) {
                return edge->getVisited();
            }
        }
        return false;
    }
    bool isProcessing() const {
        return processing;
    };
    bool getIndegree() const {
        return indegree;
    };
    double getDist() const {
        return dist;
    };
    Edge *getPath() const {
        return path;
    };
    std::vector<Edge *> getAdj() const {
        return adj;
    };
    void setVisited(bool visited) {
        this->visited=visited;
    };
    void setProcessing(bool processing) {
        this->processing=processing;
    };
    void setPred(int p) {
        this->pred=p;
    }

    int getLow() const {
        return low;
    };
    void setLow(int value) {
        this->low = value;
    };
    int getNum() const {
        return num;
    };
    void setNum(int value) {
        this->num = value;
    };

    void setIndegree(unsigned int inDegree) {
        this->indegree=inDegree;
    };
    void setDist(double dist) {
        this->dist=dist;
    };
    void setPath(Edge *path) {
        this->path=path;
    };
    Edge* addEdge(Node *dest,double  driving,double walking) {
        auto newEdge = new Edge(this, dest, driving, walking);
        adj.push_back(newEdge);
        dest->incoming.push_back(newEdge);
        return newEdge;
    }
    bool removeEdge(Node *n) {
        bool removedEdge = false;
        auto it = adj.begin();
        while (it != adj.end()) {
            Edge *edge = *it;
            Node *org = edge->getOrig();
            if (org == n) {  // Compare edge pointers, not the nodes
                it = adj.erase(it);  // Remove edge from adjacency list
                deleteEdge(edge);  // Handle additional cleanup
                removedEdge = true;
            } else {
                ++it;
            }
        }
        return removedEdge;
    }

    


    void setEdgeVisiTed(Node *dest,bool visit) {
        for (Edge *edge : adj) {
            if (edge->getDest() == dest) {
                edge->setVisited(visit);
                return;
            }
        }
    }

    void removeOutgoingEdges() {
        auto it = adj.begin();
        while (it != adj.end()) {
            Edge *edge = *it;
            it = adj.erase(it);
            deleteEdge(edge);
        }
    };


};

#endif //NODE_H



