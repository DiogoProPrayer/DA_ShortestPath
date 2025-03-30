#include <iostream>
#include "menu.h"
#include "readData.h"
#include "WalkDrive.h"

using namespace std;

/*
 * @brief Main function to run the program
 * @return 0 on success
 */
int main() {
    Graph graph;
    readData(graph);
    std::unordered_set<int> limit;
    std::vector<std::pair<int,int>> edgesToAvoid={{4,6}};
    std::vector<WalkDrive> alt;
    noRestriction(8,1,graph,0);
    menu(graph);
    return 0;
}


