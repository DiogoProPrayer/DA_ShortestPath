#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include "Graph.h"
#include "readData.h"
#include <limits>


bool compare(const std::pair<int, int>& d1, const std::pair<int, int>& d2) {
    return d1.first > d2.first;
}

inline std::vector<int> noRestriction(int source, int dest, const Graph& graph) {
    std::pair<double, int> DistNode;  // pair.first-distance to the node from the source, pair.second is the destination node
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(&compare)> dis(compare);  // min-heap for Dijkstra
    std::vector<int> ret;
    int index = graph.findNodeIndex(source);
    double drive;
    std::vector<Node*> Nodes = graph.getNodes();
    std::vector<Edge*> adj;

    // Initialize all nodes
    for (int i = 0; i < graph.getNodeSize(); i++) {
        Nodes[i]->setVisited(false);
        Nodes[i]->setDist(std::numeric_limits<double>::infinity());
    }

    if (index == -1) return ret;

    Nodes[index]->setDist(0);
    dis.push({ 0, source });

    while (!dis.empty()) {
        DistNode = dis.top();
        dis.pop();
        index = graph.findNodeIndex(DistNode.second);
        Node* sourceNode=Nodes[index];
        adj = Nodes[index]->getAdj();
        sourceNode->setVisited(true);

        for (Edge* edg : adj) {
            drive = edg->getDrivingTime();
            Node* destNode = edg->getDest();

            if (drive != 0 && !destNode->isVisited()) {
                if (sourceNode->getDist() + drive < destNode->getDist()) {
                    destNode->setDist(sourceNode->getDist() + drive);
                    destNode->setPred(sourceNode->getId());
                    dis.push({ destNode->getDist(), destNode->getId() });
                }
                if (destNode->getId() == dest) {
                    int currentLocation =destNode->getId();
                    while (currentLocation != source) {
                        std::cout<<currentLocation<<std::endl;
                        ret.push_back(currentLocation);
                        currentLocation = Nodes[graph.findNodeIndex(currentLocation)]->getPred();
                    }
                    ret.push_back(source);
                    std::reverse(ret.begin(), ret.end());
                    return ret;
                }
            }
        }
    }
    return ret;
}

int main() {
    Graph graph;
    readData(graph);
    std::vector<int> res = noRestriction(3, 4, graph);
    std::vector<int> exp={3,2,4};

}





