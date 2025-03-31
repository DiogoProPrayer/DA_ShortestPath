#ifndef BATCH_H
#define BATCH_H

#include <string>
#include <fstream>
#include "Graph.h"

/**
 * @brief Processes a restricted driving request.
 *
 * Parses avoid nodes and segments as well as an optional included node from the provided strings,
 * resets the graph nodes, calculates a driving route under imposed restrictions, and appends the result to "output.txt".
 *
 * @param graph The graph object representing nodes and edges.
 * @param s The source node as a string.
 * @param d The destination node as a string.
 * @param avoidNodes A comma-separated string of node IDs to avoid.
 * @param avoidSegments A string representing segments (as pairs) to avoid.
 * @param includeNode A string representing a node that must be included in the path.
 */
void processRestrictedDriving(Graph graph, std::string s, std::string d, std::string avoidNodes, std::string avoidSegments, std::string includeNode);

/**
 * @brief Processes a driving request without restrictions.
 *
 * Resets all nodes in the graph, calculates the best driving route (and an alternative route if available),
 * and appends the results to "output.txt".
 *
 * @param graph The graph object.
 * @param s The source node as a string.
 * @param d The destination node as a string.
 */
void processDriving(Graph graph, std::string s, std::string d);

/**
 * @brief Processes an eco (driving-walking) routing request.
 *
 * Parses the maximum walking time and nodes/segments to avoid from the input strings, resets the graph,
 * and calculates both a driving and walking route. The results are then appended to "output.txt".
 *
 * @param graph The graph object.
 * @param s The source node as a string.
 * @param d The destination node as a string.
 * @param maximumwalkingtime The maximum walking time as a string.
 * @param avoidNodes A comma-separated string of node IDs to avoid.
 * @param avoidSegments A string representing segments (as pairs) to avoid.
 */
void processEco(Graph graph, std::string s, std::string d, std::string maximumwalkingtime, std::string avoidNodes, std::string avoidSegments);

/**
 * @brief Parses a test case from an input file.
 *
 * Reads a block of lines corresponding to a test case, extracts the mode and its parameters,
 * and then calls the appropriate processing function.
 *
 * @param file The input file stream.
 * @param line The current line from the input file.
 * @param graph The graph object.
 */
void parseCase(std::ifstream &file, std::string &line, Graph graph);

/**
 * @brief Processes batch tests from an input file.
 *
 * Prompts the user for the full path of an input file containing test cases,
 * clears any previous output file, and then processes each test case.
 *
 * @param graph The graph object containing nodes and edges.
 */
void batch(Graph graph);

#endif // BATCH_H
