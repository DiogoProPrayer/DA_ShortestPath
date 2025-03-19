#ifndef GRAPH
#define GRAPH
#include <string>
#include <vector>
#include "Node.h"
#include <iostream>

class Graph {
public:
    ~Graph();

    int findNodeIndex(const int id) const {
        for (unsigned i = 0; i < Nodes.size(); i++){
            if (Nodes[i]->getId()==id ){return i;};
        }
        return -1;
    };
    Node * findNode(const Node &in) const {
        for (auto v : Nodes)
            if (v->getId() == in.getId())
                return v;
        return nullptr;
    }
    Node* findNodeByCode(const std::string &code) const{
        for (int i=0;i<Nodes.size();i++)
            if (Nodes[i]->getCode() == code)
                return Nodes[i];
        return nullptr;
    }

    bool addNode(const Node &in) {
        if (findNode(in) != nullptr){return false;}
        Nodes.push_back(new Node(in));
        return true;
    };
    bool removeNode(const int in) {
        for (auto it = Nodes.begin(); it != Nodes.end(); it++) {
            if ((*it)->getId() == in) {
                auto v = *it;
                v->removeOutgoingEdges();
                for (auto u : Nodes) {
                    u->removeEdge(v);
                }
                Nodes.erase(it);
                delete v;
                return true;
            }
        }
        return false;
    };

bool addEdge(const Node &source, const Node &dest, double driving, double walking) const{

    Node* v1 = findNode(source);
    Node* v2 = findNode(dest);

    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, driving, walking);
    return true;
}

    bool removeEdge(const Node &source, const Node &dest) const{
        Node * srcVertex = findNode(source);
        if (srcVertex == nullptr) {
            return false;
        }
        Node * destNode = findNode(dest);
        return srcVertex->removeEdge(destNode);
    };
    bool addBidirectionalEdge(const Node &sourc, const Node &dest, double driving, double walking) const {
        if (findNode(sourc)!=nullptr && findNode(dest)!=nullptr) {
            addEdge(sourc,dest,driving,walking);
            addEdge(dest,sourc,driving,walking);
            return true;
        }
        return false;

    };

    int getNumVertex() const {
        return Nodes.size();
    };
    std::vector<Node *> getNodes() const {
        return Nodes;
    };
    void printGraph() {
        for (Node *v : Nodes) {
            std::cout<< v->getLocation()<<" "<<v->getId()<<" "<<v->getCode()<<" "<<v->getParking()<<std::endl;
        }
    }

    int getNodeSize() const {
        return static_cast<int>(Nodes.size());
    }
protected:
    std::vector<Node *> Nodes;

    double ** distMatrix = nullptr;
    int **pathMatrix = nullptr;

    int findVertexIdx(const Node &in) const;
};
void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);
inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, Nodes.size());
    deleteMatrix(pathMatrix, Nodes.size());
}


#endif
