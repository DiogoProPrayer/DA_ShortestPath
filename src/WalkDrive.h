#ifndef WALKDRIVE_H
#define WALKDRIVE_H

#include <vector>
#include <limits>
#include <utility>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Graph.h"

struct singleMode{
    std::vector<int> bestpath;
    std::vector<int> alternative;
    double bestDistance;
    double alternativeDistance;

};
struct WalkDrive{
    bool parking;
    bool range;
    std::pair<std::vector<int>,double> drivingRoute;
    std::pair<std::vector<int>,double>  walkingRoute;
    int parkingNode;
    int totalTime;

};
/**
 * @brief Function made for finding alternative path by seting the nodes in the best path to visited
 * @details Complexity O(n), n-number of elements in the path vector
 * @param source The starting node ID
 * @param dest The destination node ID
 * @param path Vector with node IDs of path
 * @return std::set<int> Set with node IDs to avoid
 */
inline std::unordered_set<int> limit(int source,int dest,std::vector<int>&path){
    std:: unordered_set<int> limit;
    for(int i:path){
        if(i!=dest && i!=source){
            limit.emplace(i);
        }
    }
    return limit;
}


inline bool comparedist(const std::pair<double, int>& d1, const std::pair<double, int>& d2) {
    return d1.first > d2.first;
}



/**
 * @brief Set all nodes and edges to unvisited and set the distance for the dijkstra algorithm
 * @details Complexity O(V+E)
 * @param graph Graph object - with nodes
 */
inline void unsetNodesAndEdges(Graph &graph, int mode){
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        if(mode){
            Nodes[i]->setWalkingPred(-1);
            Nodes[i]->setWalkingDist(std::numeric_limits<double>::infinity());
        }
        else{
            Nodes[i]->setPred(-1);
            Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        }
        if(!Nodes[i]->getAdj().empty()){
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

inline void someNodesVisited(const Graph &graph,std::unordered_set<int> &limit){
    if (limit.empty()){return;}
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        if(limit.find(Nodes[i]->getId()) != limit.end()){
            Nodes[i]->setVisited(true);
        }
    }

}

/**
 * @brief Set the edges to avoid to visited
 * @details Complexity O(V + E)
 * @param graph Graph object
 * @param edgesToAvoid Vector with edges to avoid
 */
inline void someEdgesVisited(Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid){
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

inline void algorithm(int source,const Graph &graph, int mode){
    std::pair<double, int> DistNode; 
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(&comparedist)> dis(comparedist);
    int index = graph.findNodeIndex(source);
    float d;
    std::vector<Node*> Nodes = graph.getNodes();
    std::vector<Edge*> adj;
    if (mode==0)Nodes[index]->setDist(0);
    else Nodes[index]->setWalkingDist(0);
    dis.push({ 0, source });
    while (!dis.empty()) {
        DistNode = dis.top();
        dis.pop();
        index = graph.findNodeIndex(DistNode.second);
        Node* sourceNode=Nodes[index];
        adj = Nodes[index]->getAdj();
        sourceNode->setVisited(true);
        for (Edge* edg:adj) {
            d=mode? edg->getWalkingTime():edg->getDrivingTime();
            Node* destNode = edg->getDest();
            if (d !=-1 && !destNode->isVisited() && !sourceNode->isEdgeVisited(destNode)) {
                if (mode==0) {
                    if (sourceNode->getDist() + d< destNode->getDist()) {
                        destNode->setDist(sourceNode->getDist() + d);
                        destNode->setPred(sourceNode->getId());
                        dis.push({ destNode->getDist(), destNode->getId()});
                    }
                }
                else {
                    if (sourceNode->getWalkingDist() + d< destNode->getWalkingDist()) {
                        destNode->setWalkingDist(sourceNode->getWalkingDist() + d);
                        destNode->setWalkingPred(sourceNode->getId());
                        dis.push({ destNode->getWalkingDist(), destNode->getId() });
                    }
                }
            }
        }
    }



}

inline std::pair<std::vector<int>,double> getPath(int source,int dest,Graph &graph, bool mode){
    std::vector<int> path;
    double distance=0;
    int index=graph.findNodeIndex(dest);
    std::vector<Node*> Nodes = graph.getNodes();
    if(mode?Nodes[index]->getWalkingDist()==std::numeric_limits<double>::infinity():Nodes[index]->getDist()==std::numeric_limits<double>::infinity()){
        return {path,distance};
    }
    int currentlocation=dest;
    distance=mode?Nodes[index]->getWalkingDist():Nodes[index]->getDist();
    while (currentlocation!=source){
        path.push_back(currentlocation);
        currentlocation=mode?Nodes[graph.findNodeIndex(currentlocation)]->getWalkingPred() :Nodes[graph.findNodeIndex(currentlocation)]->getPred();
    }
    path.push_back(source);
    std::reverse(path.begin(),path.end());
    return {path,distance};

}
inline std::pair<std::vector<int>,double> getPathDW(int source,int dest,Graph &graph, bool mode){
    std::vector<int> path;
    double distance=0;
    int index=graph.findNodeIndex(dest);
    std::vector<Node*> Nodes = graph.getNodes();
    if(mode?Nodes[index]->getWalkingDist()==std::numeric_limits<double>::infinity():Nodes[index]->getDist()==std::numeric_limits<double>::infinity()){
        return {path,distance};
    }
    int currentlocation=dest;
    distance=mode?Nodes[index]->getWalkingDist():Nodes[index]->getDist();
    while (currentlocation!=source){
        path.push_back(currentlocation);
        currentlocation=mode?Nodes[graph.findNodeIndex(currentlocation)]->getWalkingPred() :Nodes[graph.findNodeIndex(currentlocation)]->getPred();
    }
    path.push_back(source);
    if (!mode) std::reverse(path.begin(),path.end());
    return {path,distance};

}
/**
 * @brief Find the shortest path between two nodes with no restrictions on the nodes and edges
 * @details Complexity O((V + E) log(V)+V²)
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
 inline singleMode noRestriction(int source,int dest,Graph graph,int mode){
    std::pair<std::vector<int>,double> path;
    singleMode result;
    if (graph.findNodeIndex(source)==-1 || graph.findNodeIndex(dest)==-1) {
        return result;
    }
    unsetNodesAndEdges(graph,mode);
    algorithm(source,graph,mode);
    path=getPath(source,dest,graph,mode);
    result.bestpath=path.first;
    result.bestDistance=path.second;
    std::unordered_set<int> lim=limit(source,dest,result.bestpath);
    unsetNodesAndEdges(graph,mode);
    someNodesVisited(graph,lim);
    algorithm(source,graph,mode);
    path=getPath(source,dest,graph,mode);
    result.alternative=path.first;
    result.alternativeDistance=path.second;
    return result;
}
/**
 * @brief Find the shortest path between two nodes with restrictions on the nodes and edges
 * @details Complexity O((V + E) log(V)+V²)
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
inline singleMode restrictedEdgesAndNodes(int source,int dest,Graph graph,std::unordered_set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid, int mode){
    singleMode result;
    std::pair<std::vector<int>,double> path;
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1) return result;
    std::vector<Node*> Nodes = graph.getNodes();
    unsetNodesAndEdges(graph,mode);
    someNodesVisited(graph,limit);
    someEdgesVisited(graph,edgesToAvoid);
    algorithm(source,graph,mode);
    path=getPath(source,dest,graph,mode);
    result.bestpath=path.first;
    result.bestDistance=path.second;
    return result;
}
/**
 * @brief Find the shortest path between two nodes with a node included and restrictions on the nodes and edges
 * @details Complexity O((V + E) log(V)+V²)
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param include Node ID to include in path
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
inline singleMode includeNodeWithRestrictNodesAndEdges(int source, int dest,  Graph& graph,std::unordered_set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode){
    singleMode result;
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1||graph.findNodeIndex(include)==-1)return result;
    std::vector<Node*> Nodes = graph.getNodes();
    std::pair<std::vector<int>,double> path;
    unsetNodesAndEdges(graph,mode);
    someNodesVisited(graph,limit);
    someEdgesVisited(graph,edgesToAvoid);
    algorithm(source,graph,mode);
    if(Nodes[graph.findNodeIndex(include)]->getDist()==std::numeric_limits<double>::infinity()) return result;
    path=getPath(source,include,graph,mode);
    unsetNodesAndEdges(graph,mode);
    someNodesVisited(graph,limit);
    someEdgesVisited(graph,edgesToAvoid);
    algorithm(include,graph,mode);
    if(Nodes[graph.findNodeIndex(dest)]->getDist()==std::numeric_limits<double>::infinity()) return result;
    std::pair<std::vector<int>,double> path2=getPath(include,dest,graph,mode);
    path.first.insert(path.first.end(),path2.first.begin()+1,path2.first.end());
    path.second+=path2.second;
    result.bestpath=path.first;
    result.bestDistance=path.second;
    return result;
}
/**
 * @brief Calculates driving path between two nodes
 * @details Complexity O((V + E) log(V)+V²)
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param include Node ID to include in path
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
inline singleMode driving(int source, int dest,  Graph& graph,std::unordered_set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,int include){
    if(include==-1){
        return restrictedEdgesAndNodes(source,dest,graph,limit,edgesToAvoid,0);

    }
    return includeNodeWithRestrictNodesAndEdges(source,dest,graph,limit,edgesToAvoid,include,0);

}
/**
 * @brief Calculates walking path between two nodes
 * @details Complexity O((V + E) log(V)+V²)
 * @param source The starting node ID
 * @param dest The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param include Node ID to include in path
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
inline singleMode walking(int source, int dest,  Graph& graph,std::unordered_set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,int include){
    if(edgesToAvoid.empty() && limit.empty()&& include==-1){
        return noRestriction(source,dest,graph,1);
    }
    if(include==-1){
        return restrictedEdgesAndNodes(source,dest,graph,limit,edgesToAvoid,1);

    }
    return includeNodeWithRestrictNodesAndEdges(source,dest,graph,limit,edgesToAvoid,include,1);

}

inline bool adj(int sourc, int dest, Graph &graph){
    std::vector<Node*> nodes=graph.getNodes();
    Node* source=nodes[graph.findNodeIndex(sourc)];
    for(Edge* edg:source->getAdj()){
        if(edg->getDest()->getId()==dest)
        return true;
    }
    return false;
}

inline std::unordered_set<int> getParkingNodes(Graph &graph){
    std::unordered_set<int> parkingNodes;
    std::vector<Node*> nodes=graph.getNodes();
    for(Node* node:nodes){
        if(node->getParking()){
            parkingNodes.insert(node->getId());
        }
    }
    return parkingNodes; 
}
inline bool walkcomp(const WalkDrive d1, const WalkDrive d2) {
    return d1.totalTime>d2.totalTime;
}

inline WalkDrive walkingDriving(int source, int dest,  Graph& graph,std::unordered_set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,double maxWalkingTime,std::vector<WalkDrive> &al) {
    WalkDrive result,alternative;
    if(graph.findNodeIndex(source)==-1||graph.findNodeIndex(dest)==-1)
        return result;
    std::pair<std::vector<int>,double> drivingRoute;
    std::pair<std::vector<int>,double> walkRoute;
    std::vector<Node*> nodes=graph.getNodes();
    if(adj(source,dest,graph)) return result;
    std::unordered_set<int> parkingNodes=getParkingNodes(graph);
    unsetNodesAndEdges(graph,0);
    someNodesVisited(graph,limit);
    someEdgesVisited(graph,edgesToAvoid);
    algorithm(source,graph,0);
    unsetNodesAndEdges(graph,1);
    someNodesVisited(graph,limit);
    someEdgesVisited(graph,edgesToAvoid);
    algorithm(dest,graph,1);
    Node* Node;
    int count=0;
    std::priority_queue<WalkDrive, std::vector<WalkDrive>, decltype(&walkcomp)>alt(walkcomp);
    for (int node: parkingNodes) {
        if (limit.find(node)==limit.end()) {
            Node=nodes[graph.findNodeIndex(node)];
            double walktime=Node->getWalkingDist();
            double drivetime=Node->getDist();
            if (walktime!=numeric_limits<double>::infinity() && drivetime!=numeric_limits<double>::infinity()) {
                count++;
                drivingRoute=getPathDW(source,node,graph,0);
                walkRoute=getPathDW(dest,node,graph,1);
                alternative.parking=true;
                alternative.parkingNode=node;
                alternative.range=true;
                alternative.drivingRoute=drivingRoute;
                alternative.walkingRoute=walkRoute;
                alternative.totalTime=walktime+drivetime;
                alt.push(alternative);

            }
        }

    }
    if (alt.top().walkingRoute.second<=maxWalkingTime) {
        result=alt.top();
        alt.pop();
        return result;
    }
    if (count==0) {
        result.parking=false;
        result.range=true;
    }
    else if(count!=0 && result.drivingRoute.first.empty()) {
        result.parking=true;
        result.range=false;
        if (!alt.empty()) {
            int i=alt.size();
            if (i==1) {
                al.push_back(alt.top());
                alt.pop();
            }
            else {
                al.push_back(alt.top());
                alt.pop();
                al.push_back(alt.top());
                alt.pop();
            }
        }
    }

    return result;
}

#endif
