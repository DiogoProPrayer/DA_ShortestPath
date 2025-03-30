//
// Created by buttercup on 17-03-2025.
//

#ifndef MODE_H
#define MODE_H
#include <vector>
#include <limits>
#include <utility>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Graph.h"








/**
* @brief Get the path between two nodes
* @details Complexity O(V²)
* @param source The starting node ID
* @param dest The destination node ID
* @param graph Graph object
* @return pair<vector<int>, double> - path and distance
*/
std::pair<std::vector<int>,double> getPath(int source,int dest,Graph &graph){
    std::vector<int> path;
    double distance=0;
    int index=graph.findNodeIndex(dest);
    std::vector<Node*> Nodes = graph.getNodes();
    if(Nodes[index]->getDist()==std::numeric_limits<double>::infinity()){
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

/**
 * @brief personalized compare function for the priority queue
 * @details Complexity O(1)
 * @param d1 First pair - node and distance
 * @param d2 Secon pair - node and distance
 * @return true if first pair distance >
 * @return false if second pair distance >
 */
bool compare(const std::pair<double, int>& d1, const std::pair<double, int>& d2) {
    return d1.first > d2.first;
}

/**
 * @brief Dijkstra's algorithm to find the shortest path between two nodes
 * @details Complexity O((E+V) logV)
 * @param source The starting node ID
 * @param dest The destination node ID
 * @param graph Graph object - with nodes
 * @param mode Decide between driving and walking
 */
void algorithm(int source, int dest, const Graph& graph, int mode){
    std::pair<double, int> DistNode;
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
            if (d !=-1 && !destNode->isVisited() && !sourceNode->isEdgeVisited(destNode)) {
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
 * @details Complexity O(V+E)
 * @param graph Graph object - with nodes
 */
 void unsetNodesAndEdges(Graph &graph){
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setPred(-1);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if(Nodes[i]->getAdj().empty()){
            for(Edge* edge:Nodes[i]->getAdj()){
                edge->setVisited(false);
            }
        }
    }

 }

/**
 * @brief Set the nodes to avoid to visited
 * @details Complexity O(V + E)
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
*/
 void setSomeNodesVisited(Graph &graph,std::unordered_set<int> &limit){
    if (limit.empty()){return;}
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setPred(-1);
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

/**
 * @brief Set the edges to avoid to visited
 * @details Complexity O(V + E)
 * @param graph Graph object - with nodes
 * @param edgesToAvoid Vector with edges to avoid
 */
void setSomeEdgesVisited(Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid){
    if (edgesToAvoid.empty()){return;}
    std::vector<Node*> Nodes = graph.getNodes();
    int index1;
    int index2;
    for(std::pair<int,int> edge:edgesToAvoid){
        index1=graph.findNodeIndex(edge.first);
        index2=graph.findNodeIndex(edge.second);
        Nodes[index1]->setEdgeVisited(Nodes[index2],true);
        Nodes[index2]->setEdgeVisited(Nodes[index1],true);
    }
}















#endif // MODE_H
