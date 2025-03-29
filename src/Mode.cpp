#include "Mode.h"
#include <iostream>
#include <queue>
#include <regex>


std::unordered_set<int> limit(int source, int dest, const std::vector<int>& path) {
    std::unordered_set<int> limitSet;
    for (int i : path) {
        if (i != dest) {
            limitSet.emplace(i);
        }
    }
    return limitSet;
}

std::pair<std::vector<int>, double> getPath(int source, int dest, Graph &graph) {
    std::vector<int> path;
    double distance = 0;
    int index = graph.findNodeIndex(dest);
    std::vector<Node*> Nodes = graph.getNodes();
    if (Nodes[index]->getDist() == std::numeric_limits<double>::infinity()) {
        return {path, distance};
    }
    int currentlocazion = dest;
    distance = Nodes[index]->getDist();
    while (currentlocazion != source) {
        path.push_back(currentlocazion);
        currentlocazion = Nodes[graph.findNodeIndex(currentlocazion)]->getPred();
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return {path, distance};
}

bool compare(const std::pair<double, int>& d1, const std::pair<double, int>& d2) {
    return d1.first > d2.first;
}

void algorithm(int source, int dest, const Graph& graph, int mode) {
    std::pair<double, int> DistNode;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(&compare)> dis(compare);
    int index = graph.findNodeIndex(source);
    float d;
    std::vector<Node*> Nodes = graph.getNodes();
    Nodes[index]->setDist(0);
    dis.push({0, source});

    while (!dis.empty()) {
        DistNode = dis.top();
        dis.pop();
        index = graph.findNodeIndex(DistNode.second);
        Node* sourceNode = Nodes[index];
        std::vector<Edge*> adj = sourceNode->getAdj();
        sourceNode->setVisited(true);

        for (Edge* edg : adj) {
            d = (mode == 0 ? edg->getDrivingTime() : edg->getWalkingTime());
            Node* destNode = edg->getDest();

            if (d != -1 && !destNode->isVisited() && !sourceNode->isEdgeVisited(destNode)) {
                if (sourceNode->getDist() + d < destNode->getDist()) {
                    destNode->setDist(sourceNode->getDist() + d);
                    destNode->setPred(sourceNode->getId());
                    dis.push({destNode->getDist(), destNode->getId()});
                }
            }
        }
    }
}

void unsetNodesAndEdges(Graph &graph) {
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setPred(-1);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if (!Nodes[i]->getAdj().empty()) {
            for (Edge* edge : Nodes[i]->getAdj()) {
                edge->setVisited(false);
            }
        }
    }
}

void setSomeNodesVisited(Graph &graph, std::unordered_set<int> &limitSet) {
    if (limitSet.empty()) { return; }
    std::vector<Node*> Nodes = graph.getNodes();
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
        if (limitSet.find(Nodes[i]->getId()) != limitSet.end()) {
            Nodes[i]->setVisited(true);
        }
        if (!Nodes[i]->getAdj().empty()) {
            for (Edge* edge : Nodes[i]->getAdj()) {
                edge->setVisited(false);
            }
        }
    }
}

void setSomeEdgesVisited(Graph &graph, std::vector<std::pair<int,int>> &edgesToAvoid) {
    if (edgesToAvoid.empty()) { return; }
    std::vector<Node*> Nodes = graph.getNodes();
    int index1, index2;
    for (std::pair<int,int> edge : edgesToAvoid) {
        index1 = graph.findNodeIndex(edge.first);
        index2 = graph.findNodeIndex(edge.second);
        Nodes[index1]->setEdgeVisited(Nodes[index2], true);
        Nodes[index2]->setEdgeVisited(Nodes[index1], true);
    }
}

singleMode noRestriction(int source, int dest, Graph graph, int mode) {
    std::pair<std::vector<int>, double> path;
    singleMode result;
    unsetNodesAndEdges(graph);
    algorithm(source, dest, graph, mode);
    path = getPath(source, dest, graph);
    result.bestpath = path.first;
    result.bestDistance = path.second;
    std::unordered_set<int> lim = limit(source, dest, result.bestpath);
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph, lim);
    algorithm(source, dest, graph, mode);
    path = getPath(source, dest, graph);
    result.alternative = path.first;
    result.alternativeDistance = path.second;
    return result;
}

singleMode restrictedEdgesAndNodes(int source, int dest, Graph graph,
                                   std::unordered_set<int> &limitSet,
                                   std::vector<std::pair<int,int>> &edgesToAvoid,
                                   int mode) {
    singleMode result;
    std::pair<std::vector<int>, double> path;
    if (graph.findNodeIndex(source) == -1 || graph.findNodeIndex(dest) == -1)
        return result;
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph, limitSet);
    setSomeEdgesVisited(graph, edgesToAvoid);
    algorithm(source, dest, graph, mode);
    path = getPath(source, dest, graph);
    result.bestpath = path.first;
    result.bestDistance = path.second;
    return result;
}

singleMode includeNodeWithRestrictNodesAndEdges(int source, int dest, Graph &graph,
                                                std::unordered_set<int> &limitSet,
                                                std::vector<std::pair<int,int>> &edgesToAvoid,
                                                int include, int mode) {
    singleMode result;
    if (graph.findNodeIndex(source) == -1 || graph.findNodeIndex(dest) == -1 ||
        graph.findNodeIndex(include) == -1)
        return result;
    std::pair<std::vector<int>, double> path;
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph, limitSet);
    setSomeEdgesVisited(graph, edgesToAvoid);
    algorithm(source, include, graph, mode);
    if (graph.getNodes()[graph.findNodeIndex(include)]->getDist() == std::numeric_limits<double>::infinity())
        return result;
    path = getPath(source, include, graph);
    unsetNodesAndEdges(graph);
    setSomeNodesVisited(graph, limitSet);
    setSomeEdgesVisited(graph, edgesToAvoid);
    algorithm(include, dest, graph, mode);
    if (graph.getNodes()[graph.findNodeIndex(dest)]->getDist() == std::numeric_limits<double>::infinity())
        return result;
    std::pair<std::vector<int>, double> path2 = getPath(include, dest, graph);
    path.first.insert(path.first.end(), path2.first.begin() + 1, path2.first.end());
    path.second += path2.second;
    result.bestpath = path.first;
    result.bestDistance = path.second;
    return result;
}

singleMode driving(int source, int dest, Graph &graph,
                   std::unordered_set<int> &limitSet,
                   std::vector<std::pair<int,int>> &edgesToAvoid,
                   int include) {
    if (include == -1) {
        return restrictedEdgesAndNodes(source, dest, graph, limitSet, edgesToAvoid, 0);
    }
    return includeNodeWithRestrictNodesAndEdges(source, dest, graph, limitSet, edgesToAvoid, include, 0);
}

singleMode walking(int source, int dest, Graph &graph,
                   std::unordered_set<int> &limitSet,
                   std::vector<std::pair<int,int>> &edgesToAvoid,
                   int include) {
    if (edgesToAvoid.empty() && limitSet.empty() && include == -1) {
        return noRestriction(source, dest, graph, 1);
    }
    if (include == -1) {
        return restrictedEdgesAndNodes(source, dest, graph, limitSet, edgesToAvoid, 1);
    }
    return includeNodeWithRestrictNodesAndEdges(source, dest, graph, limitSet, edgesToAvoid, include, 1);
}
