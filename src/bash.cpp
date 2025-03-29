#include <iostream>
#include <string>
#include "bash.h"
#include "Graph.h"

using namespace std;


void bash(Graph graph)
{
    string input;
    system("clear");
    cout << "Path for the input file: ";
    cin >> input;

    // Open the file
    ifstream file(input);
    if (!file.is_open()) {
        cout << "Error opening file: " << input << endl;
        return;
    }
    // Read the file line by line

    
}