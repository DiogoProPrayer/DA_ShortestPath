#include <iostream>
#include "batch.h"

using namespace std;

void processRestrictedDriving(Graph graph, string source, string destination, string avoidNodes, string avoidEdges, string includeNodes)
{
    cout << "Processing driving case..." << endl;
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
    cout << "AvoidNodes: " << avoidNodes << endl;
    cout << "AvoidSegments: " << avoidEdges << endl;
    cout << "IncludeNode: " << includeNodes << endl;

    for (auto node : graph.getNodes())
    {
        node->resetNode();
    }
    // Implement the logic for processing the driving case here - BELEM
    
}

void processDriving(Graph graph, string source, string destination)
{
    cout << "Processing driving case..." << endl;
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;

    for (auto node : graph.getNodes())
    {
        node->resetNode();
    }

    // Implement the logic for processing the driving case here - BELEM
    
}

void parseCase(ifstream &file, string &line, Graph graph)
{
    // Extract the mode from the line
    string mode = line.substr(5);
    string source, destination, avoidNodes, avoidSegments, includeNode;
    if (mode == "driving")
    {
        cout << "Mode:driving" << endl;
        getline(file, line);
        if (line.find("Source:") == 0)
        {
            source = line.substr(7);
        }
        else
        {
            cout << "Error: Source not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("Destination:") == 0)
        {
            destination = line.substr(12);
        }
        else
        {
            cout << "Error: Destination not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("AvoidNodes:") == 0)
        {
            avoidNodes = line.substr(11);
            getline(file, line);
            if (line.find("AvoidSegments") == 0)
            {
                avoidSegments = line.substr(14);
            }
            else
            {
                cout << "Error: AvoidSegments not found in test" << endl;
                return;
            }
            getline(file, line);
            if (line.find("IncludeNode:") == 0)
            {
                includeNode = line.substr(12);
            }
            else
            {
                cout << "Error: IncludeNode not found in test" << endl;
                return;
            }

            processRestrictedDriving(graph, source, destination, avoidNodes, avoidSegments, includeNode);
        }
        else if (line.find("Mode:") == 0)
        {
            processDriving(graph, source, destination);

            parseCase(file, line, graph);
        }
        else
        {
            cout << "Error: AvoidNodes not found in test" << endl;
            return;
        }
    }
    else if (mode == "driving-walking")
    {
        cout << "Mode:driving-walking" << endl;
        return;
    }
    else
    {
        cout << "Invalid mode: " << mode << endl;
        return;
    }
}

void batch(Graph graph)
{
    int ntest = 0;
    string input;
    system("clear");
    cout << "Full path for the input file: ";
    cin >> input;

    ifstream file(input);
    if (!file.is_open())
    {
        cout << "Error opening file: " << input << endl;
        return;
    }
    // Read the file line by line
    string line;
    while (getline(file, line))
    {
        // Check if the line starts with "Mode:" else continue
        if (line.find("Mode:") == 0)
        {
            parseCase(file, line, graph);
        }
    }
}