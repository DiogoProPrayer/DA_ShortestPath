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

struct singleMode{
    std::vector<int> bestpath;
    std::vector<int> alternative;
    double bestDistance;
    double alternativeDistance;
};

/**
 * @brief Function made for finding alternative path by seting the nodes in the best path to visited
 * @details Complexity O(n)
 * @param source The starting node ID
 * @param dest The destination node ID
 * @param path Vector with node IDs of path
 * @return std::unordered_set<int> Set with node IDs to avoid
 */
std::unordered_set<int> limit(int source, int dest, std::vector<int> path);

/**
* @brief Get the path between two nodes
* @details Complexity O(n)
* @param source The starting node ID
* @param dest The destination node ID
* @param graph Graph object - with nodes
* @return pair<vector<int>, double> - path and distance
*/
std::pair<std::vector<int>,double> getPath(int source, int dest, Graph &graph);

/**
 * @brief personalized compare function for the priority queue
 * @param d1 First pair - node and distance
 * @param d2 Secon pair - node and distance
 * @return true if first pair distance >
 * @return false if second pair distance >
 */
bool compare(const std::pair<double, int>& d1, const std::pair<double, int>& d2);

/**
 * @brief Dijkstra's algorithm to find the shortest path between two nodes
 * @details Complexity O((E+V) logV)
 * @param source The starting node ID
 * @param dest The destination node ID
 * @param graph Graph object - with nodes
 * @param mode Decide between driving and walking
 */
void algorithm(int source, int dest, const Graph& graph, int mode);

/**
 * @brief Set all nodes and edges to unvisited and set the distance for the dijkstra algorithm
 * @details Complexity O(V+E)
 * @param graph Graph object - with nodes
 */
void unsetNodesAndEdges(Graph &graph);

/** 
 * @brief Set the nodes to avoid to visited
 * @details Complexity O(V + E)
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
*/
void setSomeNodesVisited(Graph &graph, std::unordered_set<int> &limit);

/**
 * @brief Set the edges to avoid to visited
 * @details Complexity O(n)
 * @param graph Graph object - with nodes
 * @param edgesToAvoid Vector with edges to avoid
 */
void setSomeEdgesVisited(Graph &graph, std::vector<std::pair<int,int>> &edgesToAvoid);

/**
 * @brief Find the shortest path between two nodes with no restrictions on the nodes and edges
 * @details Complexity O((V + E) log(V))
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
singleMode noRestriction(int source, int dest, Graph graph, int mode);

/**
 * @brief Find the shortest path between two nodes with restrictions on the nodes and edges
 * @details Complexity O((V + E) log(V))
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
singleMode restrictedEdgesAndNodes(int source, int dest, Graph graph, std::unordered_set<int> &limit, std::vector<std::pair<int,int>> &edgesToAvoid, int mode);

/**
 * @brief Find the shortest path between two nodes with a node included and restrictions on the nodes and edges
 * @details Complexity O((V + E) log(V))
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param include Node ID to include in path
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
singleMode includeNodeWithRestrictNodesAndEdges(int source, int dest, Graph &graph, std::unordered_set<int> &limit, std::vector<std::pair<int,int>> &edgesToAvoid, int include, int mode);

/**
 * @brief Calculates driving path between two nodes
 * @details Complexity O((V + E) log(V))
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param include Node ID to include in path
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
singleMode driving(int source, int dest, Graph &graph, std::unordered_set<int> &limit, std::vector<std::pair<int,int>> &edgesToAvoid, int include);

/**
 * @brief Calculates walking path between two nodes
 * @details Complexity O((V + E) log(V))
 * @param source The starting node ID
 * @param destination The destination node ID
 * @param graph Graph object - with nodes
 * @param limit Set of node IDs - to mark as visited
 * @param edgesToAvoid Set of edges to avoid
 * @param include Node ID to include in path
 * @param mode Decide between driving and walking
 * @return singleMode - best path and distance
 */
singleMode walking(int source, int dest, Graph &graph, std::unordered_set<int> &limit, std::vector<std::pair<int,int>> &edgesToAvoid, int include);

#endif // MODE_H
