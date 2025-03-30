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
    unordered_set<int> lim={2};
    vector<pair<int,int>> edges;
    noRestriction(3,8,graph,0);
    noRestriction(8,1,graph,0);
    driving(5,4,graph,lim,edges,0);
    lim={};
    edges={{3,2},{7,8}};
    driving(5,4,graph,lim,edges,0);
    lim={2};
    edges={{4,7}};
    driving(5,4,graph,lim,edges,0);
    menu(graph);
    return 0;
}


