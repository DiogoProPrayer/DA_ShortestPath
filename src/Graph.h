#ifndef GRAPH
#define GRAPH
#include <string>
#include <utility>
#include <vector>
class Edge;
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
        std::vector<Edge *> adj;
        Edge *path = nullptr;
        std::vector<Edge *> incoming;
        void deleteEdge(Edge *edge);

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
    bool isVisited() const {
        return visited;
    };
    bool isProcessing() const {
        return processing;
    };
    bool getIndegree() const {
        return indegree;
    };
    double getDistance() const {
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
    Edge* addEdge(Node *dest,double  driving,double walking);
    bool removeEdge(Node *n);
    void removeOutgoingEdges() {
        auto it = adj.begin();
        while (it != adj.end()) {
            Edge *edge = *it;
            it = adj.erase(it);
            deleteEdge(edge);
        }
    };


};
class Edge {
    protected:
        Node *org;
        Node *dest;
        double drivingTime;
        double walkingTime;
        bool selected = false;
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
class Graph {
public:
    ~Graph();

    unsigned findNodeIndex(const Node &in) const {
        for (unsigned i = 0; i < Nodes.size(); i++){
            if (Nodes[i]->getId()==in.getId() ){return i;};
        }
        return -1;
    };
    Node * findNode(const Node &in) const {
        for (auto v : Nodes)
            if (v->getId() == in.getId())
                return v;
        return nullptr;
    }
    Node* findNodeByCode(const std::string &code) {
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

bool addEdge(const Node &source, const Node &dest, double driving, double walking) {

    Node* v1 = findNode(source);
    Node* v2 = findNode(dest);

    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, driving, walking);
    return true;
}

    bool removeEdge(const Node &source, const Node &dest) {
        Node * srcVertex = findNode(source);
        if (srcVertex == nullptr) {
            return false;
        }
        Node * destNode = findNode(dest);
        return srcVertex->removeEdge(destNode);
    };
    bool addBidirectionalEdge(const Node &sourc, const Node &dest, double driving, double walking) {
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

//Node


Edge* Node::addEdge(Node *dest, double driving, double walking) {
    auto newEdge = new Edge(this, dest, driving, walking);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

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

bool Node::removeEdge(Node *n) {
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


//Edge






#endif
