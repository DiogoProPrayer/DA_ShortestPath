#include <iostream>
#include "menu.h"
#include "readData.h"

using namespace std;

/*
 * @brief Main function to run the program
 * @return 0 on success
 */
int main() {
    Graph graph;
    readData(graph);

    menu(graph);
    
    return 0;
}


