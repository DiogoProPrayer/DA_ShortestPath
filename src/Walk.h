//
// Created by buttercup on 17-03-2025.
//

#ifndef WALK_H
#define WALK_H
#include <vector>
#include <limits>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>
#include "readData.h"


bool compare(const std::pair<double, int>& d1, const std::pair<double, int>& d2) {
    return d1.first > d2.first;
}


void algorithm(int source, int dest, const Graph& graph){
    std::pair<double, int> DistNode;  // pair.first-distance to the node from the source, pair.second is the destination node
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(&compare)> dis(compare);  // min-heap for Dijkstra
    int index = graph.findNodeIndex(source);
    double walk;
    std::vector<Node*> Nodes = graph.getNodes();
    std::vector<Edge*> adj;
      Nodes[index]->setDist(0);
    dis.push({ 0, source });

    while (!dis.empty()) {
        DistNode = dis.top();
        dis.pop();
        index = graph.findNodeIndex(DistNode.second);
        Node* sourceNode=Nodes[index];
        adj = Nodes[index]->getAdj();
        sourceNode->setVisited(true);

        for (Edge* edg:adj) {
            walk = edg->getDrivingTime();
            Node* destNode = edg->getDest();

            if (walk!= 0 && !destNode->isVisited() && !sourceNode->isEdgeVisited(destNode)) {
                if (sourceNode->getDist() + walk< destNode->getDist()) {
                    destNode->setDist(sourceNode->getDist() + walk);
                    destNode->setPred(sourceNode->getId());
                    dis.push({ destNode->getDist(), destNode->getId() });
                }
            }
        }
    }
}

void noRestriction(int source, int dest, const Graph& graph) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity()); 
        for(Edge* edge:Nodes[i]->getAdj()){
            edge->setVisited(false);
        }
    }
    algorithm(source,dest,graph);
  
}

std::vector<int> path(std::set<int> &limit,int source,int dest,Graph &graph) {
        std::vector<int> path;
        int index=graph.findNodeIndex(dest);
        std::vector<Node*> Nodes = graph.getNodes();
        int currentLocation =Nodes[index]->getId();
        while (currentLocation != source) {
            path.push_back(currentLocation);
            currentLocation = Nodes[graph.findNodeIndex(currentLocation)]->getPred();
            if (currentLocation!=dest) {
                limit.insert(currentLocation);
            }
        }
        path.push_back(source);
        std::reverse(path.begin(), path.end());
        return path;
}


void restrictNode(int source, int dest, const Graph& graph,std::set<int> &limit) {
    int index = graph.findNodeIndex(source);
    std::vector<Node*> Nodes = graph.getNodes();
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if(limit.contains(Nodes[i]->getId())){
            Nodes[i]->setVisited(true);
        }
        for(Edge* edge:Nodes[i]->getAdj()){
            edge->setVisited(false);
        }
    }

    algorithm(source,dest,graph);

}

std::vector<int>restrictEdges(int source,int dest,Graph graph,std::vector<std::pair<int,int>> &edgesToAvoid) {
    std::vector<Node*> Nodes = graph.getNodes();
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    int index1;
    int index2;
    for(std::pair<int,int> edge:edgesToAvoid){
        index1=graph.findNodeIndex(edge.first);
        index2=graph.findNodeIndex(edge.second);
        Nodes[index1]->setEdgeVisiTed(Nodes[index2],true);
        Nodes[index2]->setEdgeVisiTed(Nodes[index1],true);
    }
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());  
    }

    algorithm(source,dest,graph);


}

void restrictedEdgesAndNodes(int source,int dest,Graph graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid){
    std::vector<Node*> Nodes = graph.getNodes();
    int index1;
    int index2;
    for(std::pair<int,int> edge:edgesToAvoid){
        index1=graph.findNodeIndex(edge.first);
        index2=graph.findNodeIndex(edge.second);
        Nodes[index1]->setEdgeVisiTed(Nodes[index2],true);
        Nodes[index2]->setEdgeVisiTed(Nodes[index1],true);
    }
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if(limit.contains(Nodes[i]->getId())){
            Nodes[i]->setVisited(true);
        }
    }
    algorithm(source,dest,graph);

}



#endif // Walk_H
