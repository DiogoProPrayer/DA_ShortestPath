#include <iostream>
#include "batch.h"

using namespace std;


void batch(Graph graph)
{
    string input;
    system("clear");
    cout << "Full path for the input file: ";
    cin >> input;

    ifstream file(input);
    if (!file.is_open()) {
        cout << "Error opening file: " << input << endl;
        return;
    }
    // Read the file line by line

    
}