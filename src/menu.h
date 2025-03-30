#ifndef MENU_H
#define MENU_H
#include "Graph.h"
#include <iostream>
#include <string>
using namespace std;


// Custom hash function for std::pair<int, int>
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // Combine the two hashes
    }
};

/**
 * @brief Displays the menu for selecting a driving route
 * @param graph Reference to the Graph object
 */
void menuDrivingRoute(Graph graph);

/**
 * @brief Displays the menu for selecting an eco-friendly route
 * @param graph Reference to the Graph object
 */
void menuEcoRoute(Graph graph);

/**
 * @brief Main menu function for the program
 * @param graph Reference to the Graph object
 */
void menu(Graph graph);

#endif