//
// Created by buttercup on 17-03-2025.
//

#ifndef MODE_H
#define MODE_H
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


void algorithm(int source, int dest, const Graph& graph, int mode){
    std::pair<double, int> DistNode;  // pair.first-distance to the node from the source, pair.second is the destination node
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(&compare)> dis(compare); 
    int index = graph.findNodeIndex(source);
    float d;
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
            d=mode==0? edg->getDrivingTime():edg->getWalkingTime();
            Node* destNode = edg->getDest();

            if (d != -1 && !destNode->isVisited() && !sourceNode->isEdgeVisited(destNode)) {
                if (sourceNode->getDist() + d< destNode->getDist()) {
                    destNode->setDist(sourceNode->getDist() + d);
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
void noRestriction(int source, int dest,Graph &graph,int mode) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1){ 
        std::cout <<"one of the nodes is invalid \n";
        return ;
    } 
    unsetNodesAndEdges(graph);
    algorithm(source,dest,graph,mode);

}


void restrictNode(int source, int dest,  Graph& graph,std::set<int> &limit,int mode) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    setSomeNodesVisited(graph,limit);
    algorithm(source,dest,graph,mode);
}

void restrictEdges(int source,int dest,Graph graph,std::vector<std::pair<int,int>> &edgesToAvoid,int mode) {
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    unsetNodesAndEdges(graph);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(source,dest,graph,mode);
}

void restrictedEdgesAndNodes(int source,int dest,Graph graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid, int mode){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    setSomeEdgesVisited(graph,edgesToAvoid);
    setSomeNodesVisited(graph,limit);
    algorithm(source,dest,graph,mode);

}


void includeNode(int source,int dest,Graph &graph,int include, int mode){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1||graph.findNodeIndex(include)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph);
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
}
void includeNodeWithRestrictEdges(int source,int dest,Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode){
    setSomeEdgesVisited(graph,edgesToAvoid);
    std::vector<Node*> Nodes = graph.getNodes();
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
}
void includeNodeWithRestrictNodes(int source, int dest,  Graph& graph,std::set<int> &limit,int include,int mode){
    setSomeNodesVisited(graph,limit);
    std::vector<Node*> Nodes = graph.getNodes();
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
}

void includeNodeWithRestrictNodesAndEdges(int source, int dest,  Graph& graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode){
    setSomeEdgesVisited(graph,edgesToAvoid);
    setSomeNodesVisited(graph,limit);
    std::vector<Node*> Nodes = graph.getNodes();
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity())
        return;
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity())
        return;

}
std::pair<std::vector<int>,double> getPath(int source,int dest,Graph &graph){
    std::vector<int> path;
    double distance=0;
    int index=graph.findNodeIndex(dest);
    std::vector<Node*> Nodes = graph.getNodes();
    if(Nodes[index]->getDist()==std::numeric_limits<double>::infinity()){
        std::cout<<"No path found \n";
        return {path,distance};
    }
    int currentlocazion=dest;
    distance=Nodes[index]->getDist();
    while (currentlocazion!=source){
        path.push_back(currentlocazion);
        index=Nodes[graph.findNodeIndex(currentlocazion)]->getPred();
    }
    path.push_back(source);
    std::reverse(path.begin(),path.end());
    return {path,distance};

}

std::set<int> limit(int source,int dest,std::pair<std::vector<int>,double> path){
    std::set<int> limit;
    for(int i:path.first){
        if(i!=dest && i!=dest){
            limit.emplace(i);
        }
    }
    return limit;
}



#endif // MODE_H
