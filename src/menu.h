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


void menuDrivingRoute(Graph graph);

void menuEcoRoute(Graph graph);

void menu(Graph graph);

#endif