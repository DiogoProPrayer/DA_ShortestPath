#include <iostream>
#include "menu.h"
#include "readData.h"

using namespace std;

int main() {
    Graph graph;
    readData(graph);


    menu(graph);
    
    return 0;
}


