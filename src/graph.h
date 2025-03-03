#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <utility>
#include <vector>
#include "node.h"

using namespace std;

// Class graph
class Graph {
    protected:

        // Data
        vector<Node *> Nodes;
        double ** distMatrix = nullptr;
        int **pathMatrix = nullptr;
    public:

        // Destructor
        ~Graph() {
            deleteMatrix(distMatrix, Nodes.size());
            deleteMatrix(pathMatrix, Nodes.size());
            for (auto node : Nodes) {
              delete node;
            }
        }

        // Getters
        int getNumVertex() const {
            return Nodes.size();
        }
        vector<Node *> getNodes() const {
            return Nodes;
        }

        // Functions
        // Find node index
        int findNodeIndex(const Node &in) const {
            for (size_t i = 0; i < Nodes.size(); i++){
                if (Nodes[i]->getId() == in.getId()){
                  return i;
                }
            }
            return -1;
        }

        // Find node
        Node *findNode(const Node &in) const {
            for (auto v : Nodes){
                if (v->getId() == in.getId()){
                    return v;
                }
            }
            return nullptr;
        }

        // Add node
        bool addNode(const Node &in) {
            if (findNode(in) != nullptr){
              return false;
            }
            Nodes.push_back(new Node(in));
            return true;
        }

        // Remove node
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

        // Add edge
        bool addEdge(const Node &orig, const Node &dest, double drivingTime, double walkingTime) {
            Node* v1 = findNode(orig);
            Node* v2 = findNode(dest);

            if (v1 == nullptr || v2 == nullptr) {
                return false;
            }

            v1->addEdge(v2, drivingTime, walkingTime);
            return true;
        }

        // Remove edge
        bool removeEdge(const Node &orig, const Node &dest) {
            Node * origVertex = findNode(orig);
            if (origVertex == nullptr) {
                return false;
            }
            Node *destNode = findNode(dest);
            return origVertex->removeEdge(destNode);
        }

        // Add bidirectional edge
        bool addBidirectionalEdge(const Node &orig, const Node &dest, double drivingTime, double walkingTime) {
            bool e1 = addEdge(orig, dest, drivingTime, walkingTime);
            bool e2 = addEdge(dest, orig, drivingTime, walkingTime);
            return e1 && e2;
        }

        // Find vertex index
        int findVertexIdx(const Node &in) const {
          for (size_t i = 0; i < Nodes.size(); i++){
            if (Nodes[i]->getId() == in.getId()){
              return i;
            }
          }
          return -1;
        }

        // Delete matrix
        void deleteMatrix(int **m, int n) {
            if (m != nullptr) {
                for (int i = 0; i < n; i++)
                    if (m[i] != nullptr)
                        delete [] m[i];
                delete [] m;
            }
        }

        // Delete matrix
        void deleteMatrix(double **m, int n) {
            if (m != nullptr) {
                for (int i = 0; i < n; i++)
                    if (m[i] != nullptr)
                        delete [] m[i];
                delete [] m;
            }
        }
};

#endif