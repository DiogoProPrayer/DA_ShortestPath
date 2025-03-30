#include <iostream>
#include "batch.h"
#include "menu.h"
#include <unordered_set>
#include <regex>
#include "driving-walking.h"

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
    int intsource = stoi(source);
    int intdest = stoi(destination);

    cout << "Source: " << intsource << endl;
    cout << "Destination: " << intdest << endl;

    for (auto node : graph.getNodes())
    {
        node->resetNode();
    }

    // Implement the logic for processing the driving case here - BELEM
}

void processEco(Graph graph, string s, string d, string maximumwalkingtime, string avoidNodes, string avoidSegments)
{
    int source = stoi(s);
    int destination = stoi(d);
    double maxWalk = stod(maximumwalkingtime);

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

    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
    cout << "MaxWalkTime: " << maxWalk << endl;

    cout << "AvoidNodes: ";
    for (auto node : avoidNodesSet)
    {
        cout << node << " ";
    }
    cout << endl;
    cout << "AvoidSegments: ";
    for (auto edge : avoidSegmentsSet)
    {
        cout << "(" << edge.first << "," << edge.second << ") ";
    }
    cout << endl;

    for (auto node : graph.getNodes())
    {
        node->resetNode();
    }
    // open file output.txt to append text
    ofstream out("output.txt", ios::app);
    if (!out.is_open())
    {
        cout << "Error opening file: output.txt" << endl;
        return;
    }

    DrivingWalking drivingWalking(graph, source, destination, maxWalk, avoidNodesSet, avoidSegmentsSet);
    DrivingWalkingResult result = drivingWalking.calculateRoute();
    if (result.no_parking || result.no_range)
    {
        if (result.no_parking && !result.no_range)
        {
            out << "\n\nSource:" << source << endl;
            out << "Destination:" << destination << endl;
            out << "DrivingRoute:none" << endl;
            out << "ParkingNode:none" << endl;
            out << "WalkingRoute:none" << endl;
            out << "TotalTime:" << endl;
            out << "Message:There are no available parking lots close to the destination." << endl;
        }
        else if (result.no_range && !result.no_parking)
        {
            out << "\n\nSource:" << source << endl;
            out << "Destination:" << destination << endl;
            out << "DrivingRoute:none" << endl;
            out << "ParkingNode:none" << endl;
            out << "WalkingRoute:none" << endl;
            out << "TotalTime:" << endl;
            if (maxWalk == 1)
            {
                out << "Message:No possible route with a maximum walking time of " << maxWalk << " minute." << endl;
            }
            else
            {
                out << "Message:No possible route with a maximum walking time of " << maxWalk << " minutes." << endl;
            }
        }
        else if (result.no_range && result.no_parking)
        {
            out << "\n\nSource:" << source << endl;
            out << "Destination:" << destination << endl;
            out << "DrivingRoute:none" << endl;
            out << "ParkingNode:none" << endl;
            out << "WalkingRoute:none" << endl;
            out << "TotalTime:" << endl;
            out << "Message:There are no available parking lots close and no possible route with a maximum walking time of " << maxWalk << " minutes." << endl;
        }

        pair<DrivingWalkingResult, DrivingWalkingResult> res = drivingWalking.alternativeRoutes();

        if (res.first.no_parking || res.first.no_range)
        {
            return;
        }
        out << "\n\nSource:" << source << endl;
        out << "Destination:" << destination << endl;
        out << "DrivingRoute1:";
        out << res.first.driving_route[0];
        for (int i = 1; i < res.first.driving_route.size(); i++)
        {
            out << "," << res.first.driving_route[i];
        }
        out << "(" << res.first.driving_time << ")" << endl;
        out << "ParkingNode1: " << res.first.parking_node << endl;
        out << "WalkingRoute1:";
        out << res.first.walking_route[0];
        for (int i = 1; i < res.first.walking_route.size(); i++)
        {
            out << "," << res.first.walking_route[i];
        }
        out << "(" << res.first.walking_time << ")" << endl;
        out << "TotalTime1:" << res.first.driving_time + res.first.walking_time << endl;

        if (res.second.no_parking || res.second.no_range)
        {
            out << "DrivingRoute2:none" << endl;
            out << "ParkingNode2:none" << endl;
            out << "WalkingRoute2:none" << endl;
            out << "TotalTime2:" << endl;
            return;
        }

        out << "DrivingRoute2:";
        out << res.second.driving_route[0];
        for (int i = 1; i < res.second.driving_route.size(); i++)
        {
            out << "," << res.second.driving_route[i];
        }
        out << "(" << res.second.driving_time << ")" << endl;
        out << "ParkingNode2: " << res.second.parking_node << endl;
        out << "WalkingRoute2:";
        out << res.second.walking_route[0];
        for (int i = 1; i < res.second.walking_route.size(); i++)
        {
            out << "," << res.second.walking_route[i];
        }
        out << "(" << res.second.walking_time << ")" << endl;
        out << "TotalTime2:" << res.second.driving_time + res.second.walking_time << endl;
    }
    else
    {
        out << "\n\nSource:" << source << endl;
        out << "Destination:" << destination << endl;
        out << "DrivingRoute:";
        out << result.driving_route[0];
        for (int i = 1; i < result.driving_route.size(); i++)
        {
            out << "," << result.driving_route[i];
        }
        out << "(" << result.driving_time << ")" << endl;
        out << "ParkingNode: " << result.parking_node << endl;
        out << "WalkingRoute:";
        out << result.walking_route[0];
        for (int i = 1; i < result.walking_route.size(); i++)
        {
            out << "," << result.walking_route[i];
        }
        out << "(" << result.walking_time << ")" << endl;
        out << "TotalTime:" << result.driving_time + result.walking_time << endl;
    }

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
        if (line.find("MaxWalkTime:") == 0)
        {
            maxWalk = line.substr(12);
        }
        else
        {
            cout << "Error: MaxWalkTime not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("AvoidNodes:") == 0)
        {
            avoidNodes = line.substr(11);
        }
        else
        {
            cout << "Error: AvoidNodes not found in test" << endl;
            return;
        }
        getline(file, line);
        if (line.find("AvoidSegments:") == 0)
        {
            avoidSegments = line.substr(14);
        }
        else
        {
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

    // If there is a file called output,txt, delete it
    remove("output.txt");

    while (getline(file, line))
    {
        // Check if the line starts with "Mode:" else continue
        if (line.find("Mode:") == 0)
        {
            parseCase(file, line, graph);
        }
    }
}