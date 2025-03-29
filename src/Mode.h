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

// Structure to store the results of a route calculation.
struct singleMode {
    std::vector<int> bestpath;
    std::vector<int> alternative;
    double bestDistance;
    double alternativeDistance;
};

// Function declarations

/**
 * @brief Creates a set of nodes (except destination) from a given path.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param path The vector of node IDs in the path.
 * @return std::unordered_set<int> The set of nodes to avoid.
 */
std::unordered_set<int> limit(int source, int dest, const std::vector<int>& path);

/**
 * @brief Retrieves the path and its total distance between two nodes after running Dijkstra.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @return A pair consisting of a vector of node IDs and the total distance.
 */
std::pair<std::vector<int>, double> getPath(int source, int dest, Graph &graph);

/**
 * @brief Compare function for the priority queue (Dijkstra).
 * @param d1 First pair: (distance, node ID).
 * @param d2 Second pair: (distance, node ID).
 * @return true if d1.first > d2.first.
 */
bool compare(const std::pair<double, int>& d1, const std::pair<double, int>& d2);

/**
 * @brief Dijkstra's algorithm to compute shortest path between two nodes.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @param mode 0 for driving, 1 for walking.
 */
void algorithm(int source, int dest, const Graph& graph, int mode);

/**
 * @brief Resets all nodes and edges in the graph for a new search.
 * @param graph The Graph object.
 */
void unsetNodesAndEdges(Graph &graph);

/**
 * @brief Marks a set of nodes as visited in the graph.
 * @param graph The Graph object.
 * @param limit The set of node IDs to mark as visited.
 */
void setSomeNodesVisited(Graph &graph, std::unordered_set<int> &limit);

/**
 * @brief Marks a list of edges as visited in the graph.
 * @param graph The Graph object.
 * @param edgesToAvoid A vector of edges (pairs of node IDs) to mark as visited.
 */
void setSomeEdgesVisited(Graph &graph, std::vector<std::pair<int,int>> &edgesToAvoid);

/**
 * @brief Calculates the shortest path with no restrictions.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @param mode 0 for driving, 1 for walking.
 * @return singleMode The resulting route and distances.
 */
singleMode noRestriction(int source, int dest, Graph graph, int mode);

/**
 * @brief Calculates the shortest path with restrictions on nodes and edges.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @param limit The set of node IDs to mark as visited (avoid).
 * @param edgesToAvoid The vector of edges (pairs) to avoid.
 * @param mode 0 for driving, 1 for walking.
 * @return singleMode The resulting route and distance.
 */
singleMode restrictedEdgesAndNodes(int source, int dest, Graph graph,
                                   std::unordered_set<int> &limit,
                                   std::vector<std::pair<int,int>> &edgesToAvoid,
                                   int mode);

/**
 * @brief Calculates the shortest path that must include a given node with restrictions.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @param limit The set of node IDs to mark as visited.
 * @param edgesToAvoid The vector of edges to avoid.
 * @param include The node ID that must be included.
 * @param mode 0 for driving, 1 for walking.
 * @return singleMode The resulting route and distance.
 */
singleMode includeNodeWithRestrictNodesAndEdges(int source, int dest, Graph &graph,
                                                std::unordered_set<int> &limit,
                                                std::vector<std::pair<int,int>> &edgesToAvoid,
                                                int include, int mode);

/**
 * @brief Calculates the driving route between two nodes with optional restrictions.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @param limit The set of nodes to avoid.
 * @param edgesToAvoid The vector of edges to avoid.
 * @param include The node ID that must be included (-1 if none).
 * @return singleMode The resulting driving route and distance.
 */
singleMode driving(int source, int dest, Graph &graph,
                   std::unordered_set<int> &limit,
                   std::vector<std::pair<int,int>> &edgesToAvoid,
                   int include);

/**
 * @brief Calculates the walking route between two nodes with optional restrictions.
 * @param source The starting node ID.
 * @param dest The destination node ID.
 * @param graph The Graph object.
 * @param limit The set of nodes to avoid.
 * @param edgesToAvoid The vector of edges to avoid.
 * @param include The node ID that must be included (-1 if none).
 * @return singleMode The resulting walking route and distance.
 */
singleMode walking(int source, int dest, Graph &graph,
                   std::unordered_set<int> &limit,
                   std::vector<std::pair<int,int>> &edgesToAvoid,
                   int include);

#endif // MODE_H
