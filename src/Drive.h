//
// Created by buttercup on 17-03-2025.
//

#ifndef DRIVE_H
#define DRIVE_H
#include <vector>
#include <limits>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>
#include "readData.h"


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
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(&compare)> dis(compare); 
    int index = graph.findNodeIndex(source);
    double drive;
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
            drive = edg->getDrivingTime();
            Node* destNode = edg->getDest();

            if (drive != 0 && !destNode->isVisited() && !sourceNode->isEdgeVisited(destNode)) {
                if (sourceNode->getDist() + drive < destNode->getDist()) {
                    destNode->setDist(sourceNode->getDist() + drive);
                    destNode->setPred(sourceNode->getId());
                    dis.push({ destNode->getDist(), destNode->getId() });
                }
            }
        }
    }
}


 void unsetNodesAndEdges(Graph &graph){
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if(Nodes[i]->getAdj().empty()){
            for(Edge* edge:Nodes[i]->getAdj()){
                edge->setVisited(false);
            }
        }
    }

 }
 void setSomeNodesVisited(Graph &graph,std::set<int> &limit){
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if(limit.find(Nodes[i]->getId()) != limit.end()){
            Nodes[i]->setVisited(true);
        }
        if(!Nodes[i]->getAdj().empty()){
            for(Edge* edge:Nodes[i]->getAdj()){
                edge->setVisited(false);
            }

        }
    }

 }
void setSomeEdgesVisited(Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid){
    std::vector<Node*> Nodes = graph.getNodes();
    int index1;
    int index2;
    for(std::pair<int,int> edge:edgesToAvoid){
        index1=graph.findNodeIndex(edge.first);
        index2=graph.findNodeIndex(edge.second);
        Nodes[index1]->setEdgeVisiTed(Nodes[index2],true);
        Nodes[index2]->setEdgeVisiTed(Nodes[index1],true);
    } 
}
void noRestriction(int source, int dest,Graph &graph) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return ;
    unsetNodesAndEdges(graph);
    algorithm(source,dest,graph);

}


void restrictNode(int source, int dest,  Graph& graph,std::set<int> &limit) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    setSomeNodesVisited(graph,limit);
    algorithm(source,dest,graph);
}

void restrictEdges(int source,int dest,Graph graph,std::vector<std::pair<int,int>> &edgesToAvoid) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    unsetNodesAndEdges(graph);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(source,dest,graph);
}

void restrictedEdgesAndNodes(int source,int dest,Graph graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    setSomeEdgesVisited(graph,edgesToAvoid);
    setSomeNodesVisited(graph,limit);
    algorithm(source,dest,graph);

}


void includeNodes(int source,int dest,Graph &graph,std::set<int> include){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph);
        

}






#endif // DRIVE_H
