//
// Created by buttercup on 17-03-2025.
//
#include <vector>
#include <limits>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>
#include "readData.h"


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
        currentlocazion=Nodes[graph.findNodeIndex(currentlocazion)]->getPred();
    }
    path.push_back(source);
    std::reverse(path.begin(),path.end());
    return {path,distance};

}



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
/**
 * @brief Set all nodes and edges to unvisited and set the distance for the dijkstra algorithm
 *
 * @details Complexity O(V+E)
 *
 * @param graph
 */


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
    setSomeNodesVisited(graph,limit);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(source,dest,graph,mode);

}
/**
 * @brief Find the shortest path between two nodes with a node included
 *
 * @details Complexity O()
 *
 * @param source
 * @param dest
 * @param graph
 * @param include
 * @param mode
 */


void includeNode(int source,int dest,Graph &graph,int include, int mode, std::pair<std::vector<int>,double> &path){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1||graph.findNodeIndex(include)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph);
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    path=getPath(source,include,graph);
    unsetNodesAndEdges(graph);
    algorithm(include,dest,graph,mode);
    std::pair<std::vector<int>,double> path2=getPath(include,dest,graph);
    path.first.insert(path.first.end(),path2.first.begin()+1,path2.first.end());
    path.second+=path2.second;
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
}

void includeNodeWithRestrictEdges(int source,int dest,Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode,std::pair<std::vector<int>,double> &path){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1||graph.findNodeIndex(include)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    path=getPath(source,include,graph);
    unsetNodesAndEdges(graph);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
    std::pair<std::vector<int>,double> path2=getPath(include,dest,graph);
    path.first.insert(path.first.end(),path2.first.begin()+1,path2.first.end());
    path.second+=path2.second;
}

void includeNodeWithRestrictNodes(int source, int dest,  Graph& graph,std::set<int> &limit,int include,int mode,std::pair<std::vector<int>,double> &path){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1||graph.findNodeIndex(include)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph,limit);
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    path=getPath(source,include,graph);
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph,limit);
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
    std::pair<std::vector<int>,double> path2=getPath(include,dest,graph);
    path.first.insert(path.first.end(),path2.first.begin()+1,path2.first.end());
    path.second+=path2.second;
}


void includeNodeWithRestrictNodesAndEdges(int source, int dest,  Graph& graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode,std::pair<std::vector<int>,double> &path){
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1||graph.findNodeIndex(include)==-1) return;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph,limit);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(source,include,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return;
    path=getPath(source,include,graph);
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph,limit);
    setSomeEdgesVisited(graph,edgesToAvoid);
    algorithm(include,dest,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return;
    std::pair<std::vector<int>,double> path2=getPath(include,dest,graph);
    path.first.insert(path.first.end(),path2.first.begin()+1,path2.first.end());
    path.second+=path2.second;
}

/**
 * @brief Function made for finding alternative path by seting the nodes in the best path to visited
 *
 *  @details Complexity O()
 *
 * @param source
 * @param dest
 * @param path
 * @return std::set<int>
 */

std::set<int> limit(int source,int dest,std::pair<std::vector<int>,double> path){
    std::set<int> limit;
    for(int i:path.first){
        if(i!=dest && i!=dest){
            limit.emplace(i);
        }
    }
    return limit;
}


int main() {
    Graph graph;
    readData(graph);
    std::vector<std::pair<int,int>> edgesToAvoid={{497,1058},{512,832}};
    std::set<int>lim={46};
    std::pair<std::vector<int>,double> path;
    includeNodeWithRestrictNodesAndEdges(5,432,graph,lim,edgesToAvoid,4,1,path);
    for (int i:path.first) {
        std::cout<<i<<" ";
    }
    std::cout<<path.second<<"\n";

}


