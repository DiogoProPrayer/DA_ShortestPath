#include <iostream>
#include "batch.h"
#include "menu.h"
#include <unordered_set>
#include <regex>

using namespace std;

void processRestrictedDriving(Graph graph, string source, string destination, string avoidNodes, string avoidEdges, string includeNodes)
{
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
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;

    for (auto node : graph.getNodes())
    {
        node->resetNode();
    }

    // Implement the logic for processing the driving case here - BELEM
    
}

void processEco(Graph graph, string source, string destination, string maxWalk, string avoidNodes, string avoidSegments){
    int intsource = stoi(source);
    int intdest = stoi(destination);
    double doubWalk = stod(maxWalk);

    // Parse the input
    unordered_set<int> avoidNodesSet;
    if (!avoidNodes.empty())
    {
        size_t pos = 0;
        while ((pos = avoidNodes.find(",")) != string::npos)
        {
            avoidNodesSet.insert(stoi(avoidNodes.substr(0, pos)));
            avoidNodes.erase(0, pos + 1);
        }
        avoidNodesSet.insert(stoi(avoidNodes));
    }

    unordered_set<pair<int, int>, pair_hash> avoidSegmentsSet;

    regex segmentRegex(R"(\((\d+),(\d+)\))");
    smatch match;

    string::const_iterator searchStart(avoidSegments.cbegin());
    while (regex_search(searchStart, avoidSegments.cend(), match, segmentRegex))
    {
        int id1 = stoi(match[1].str());
        int id2 = stoi(match[2].str());
        avoidSegmentsSet.insert({id1, id2});
        avoidSegmentsSet.insert({id2, id1});
        searchStart = match.suffix().first;
    }

    cout << "Source: " << intsource << endl;
    cout << "Destination: " << intdest << endl;
    cout<< "MaxWalkTime: " << doubWalk << endl;

    cout << "AvoidNodes: ";
    for(auto node: avoidNodesSet){
        cout<<node<< " ";
    }
    cout<<endl;
    cout << "AvoidSegments: ";
    for(auto edge: avoidSegmentsSet){
        cout<<"("<<edge.first<<","<<edge.second<<") ";
    }
    cout<<endl;
    
    return;
}


void parseCase(ifstream &file, string &line, Graph graph)
{
    // Extract the mode from the line
    string mode = line.substr(5);
    string source, destination, avoidNodes, avoidSegments, includeNode, maxWalk;
    if (mode == "driving")
    {
        cout << "\n\nMode:driving" << endl;
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
            processDriving(graph, source, destination);
            return;
        }
    }
    else if (mode == "driving-walking")
    {
        cout << "\n\nMode:driving-walking" << endl;
        getline(file, line);
        if (line.find("Source:")==0)
        {
            source = line.substr(7);
        } else {
            cout << "Error: Source not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("Destination:")==0)
        {
            destination = line.substr(12);
        } else {
            cout << "Error: Destination not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("MaxWalkTime:")==0)
        {
            maxWalk = line.substr(12);
        } else {
            cout << "Error: MaxWalkTime not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("AvoidNodes:")==0)
        {
            avoidNodes = line.substr(11);
        } else {
            cout << "Error: AvoidNodes not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("AvoidSegments:")==0)
        {
            avoidSegments = line.substr(14);
        } else {
            cout << "Error: AvoidSegments not found in test" << endl;
            return;
        }

        processEco(graph, source, destination, maxWalk, avoidNodes, avoidSegments);
        
        
        



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