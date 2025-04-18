#include <iostream>
#include "Graph.h"

int Graph::findNodeIndex(const int id) const
{
    for (unsigned i = 0; i < Nodes.size(); i++)
    {
        if (Nodes[i]->getId() == id)
        {
            return i;
        }
    }
    return -1;
}

Node *Graph::findNode(const Node &in) const
{
    for (auto v : Nodes)
        if (v->getId() == in.getId())
            return v;
    return nullptr;
}

Node *Graph::findNodeByCode(const std::string &code) const
{
    for (int i = 0; i < Nodes.size(); i++)
        if (Nodes[i]->getCode() == code)
            return Nodes[i];
    return nullptr;
}

bool Graph::addNode(const Node &in)
{
    if (findNode(in) != nullptr)
    {
        return false;
    }
    Nodes.push_back(new Node(in));
    return true;
}

bool Graph::addEdge(const Node &source, const Node &dest, double driving, double walking) const
{
    if (driving <-1 || walking < -1)
    {
        return false;
    }
    Node *v1 = findNode(source);
    Node *v2 = findNode(dest);
    if (v1 == nullptr || v2 == nullptr)
    {
        return false;
    }
    v1->addEdge(v2, driving, walking);
    return true;
}

bool Graph::addBidirectionalEdge(const Node &source, const Node &dest, double driving, double walking) const
{
    if (findNode(source) != nullptr && findNode(dest) != nullptr)
    {
        addEdge(source, dest, driving, walking);
        addEdge(dest, source, driving, walking);
        return true;
    }
    return false;
}

int Graph::getNumVertex() const
{
    return Nodes.size();
}

std::vector<Node *> Graph::getNodes() const
{
    return Nodes;
}

void Graph::printGraph()
{
    for (Node *v : Nodes)
    {
        std::cout << v->getLocation() << " " << v->getId() << " " << v->getCode() << " " << v->getParking() << std::endl;
    }
}

int Graph::getNodeSize() const
{
    return static_cast<int>(Nodes.size());
}

Node *Graph::getNode(int idx) const
{
    if (idx < 0 || idx > Nodes.size())
    {
        std::cout << "Invalid Node index" << std::endl;
        std::cout << "idx is " << idx << " and Nodes.size() is " << Nodes.size() << std::endl;
        return nullptr;
    }
    return Nodes[idx - 1];
}

Graph::~Graph()
{
    deleteMatrix(distMatrix, Nodes.size());
    deleteMatrix(pathMatrix, Nodes.size());
}

void deleteMatrix(int **m, int n)
{
    if (m != nullptr)
    {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

void deleteMatrix(double **m, int n)
{
    if (m != nullptr)
    {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}