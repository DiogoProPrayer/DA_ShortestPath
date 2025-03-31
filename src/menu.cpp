#include <iostream>
#include <string>
#include <unordered_set>
#include "menu.h"
#include <regex>
#include "driving-walking.h"
#include "drive.h"
using namespace std;

// Color macros
#define COLOR_BLUE_HEADER "\033[1;97;44m"  // Bright white on blue
#define COLOR_GREEN_HEADER "\033[1;97;42m" // Bright white on green
#define COLOR_RED "\033[1;31m"             // Red
#define COLOR_GREEN "\033[1;32m"           // Green
#define COLOR_YELLOW "\033[1;33m"          // Yellow
#define COLOR_CYAN "\033[1;36m"            // Cyan
#define COLOR_MAGENTA "\033[1;35m"         // Magenta
#define COLOR_RESET "\033[0m"              // Reset

void reset()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menuDrivingRoute(Graph graph)
{
    int option;
    cout << "\n\n"; // Extra space before header
    cout << COLOR_BLUE_HEADER << "        ROUTE PLANNING - DRIVING        " << COLOR_RESET << endl;
    cout << COLOR_GREEN << "1 - Independent Route Planning (T2.1)" << COLOR_RESET << endl;
    cout << COLOR_GREEN << "2 - Restricted Route Planning (T2.2)" << COLOR_RESET << endl;
    cout << COLOR_RED << "0 - Back" << COLOR_RESET << endl;
    cout << COLOR_YELLOW << "Enter your choice: " << COLOR_RESET;
    cin >> option;
    reset();

    if (option == 1)
    {
        string source, destination;
        cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
        cin >> source;
        reset();
        cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
        cin >> destination;
        reset();
        cout << COLOR_GREEN << "Calculating best and alternative routes..." << COLOR_RESET << endl;
        singleMode result = noRestriction(stoi(source), stoi(destination), graph, 0);
        cout << COLOR_YELLOW << "\n\nSource: " << source << COLOR_RESET << endl;
        cout << COLOR_YELLOW << "Destination: " << destination << COLOR_RESET << endl;
        cout << COLOR_GREEN << "Best path: ";
        if (result.bestpath.empty())
        {
            cout << COLOR_RED << "No possible route" << COLOR_RESET << endl;
        }
        else
        {
            for (int i = 0; i < result.bestpath.size(); i++)
            {
                cout << result.bestpath[i] << " ";
            }
            cout << "(" << result.bestDistance << ")" << endl;
        }
        cout << COLOR_RESET;
        cout << COLOR_GREEN << "Alternative path: " << COLOR_GREEN;
        if (result.alternative.empty())
        {
            cout << COLOR_RED << "No possible route" << COLOR_RESET << endl;
        }
        else
        {
            for (int i = 0; i < result.alternative.size(); i++)
            {
                cout << result.alternative[i] << " ";
            }
            cout << "(" << result.alternativeDistance << ")" << endl;
        }
    }
    else if (option == 2)
    {
        string source, destination, avoidNodes, avoidSegments, includeNode;
        cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
        cin >> source;
        reset();
        int sourc = stoi(source);
        cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
        cin >> destination;
        reset();
        int dest = stoi(destination);
        cout << COLOR_CYAN << "Enter nodes to avoid (comma-separated, or empty): " << COLOR_RESET;
        getline(cin, avoidNodes);
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
        cout << COLOR_MAGENTA << "Enter road segments to avoid ((id,id), or empty): " << COLOR_RESET;
        getline(cin, avoidSegments);
        vector<pair<int, int>> avoidEdges;
        regex segmentRegex(R"(\((\d+),(\d+)\))");
        smatch match;
        string::const_iterator searchStart(avoidSegments.cbegin());
        while (regex_search(searchStart, avoidSegments.cend(), match, segmentRegex))
        {
            int id1 = stoi(match[1].str());
            int id2 = stoi(match[2].str());
            avoidEdges.push_back({id1, id2});
            searchStart = match.suffix().first;
        }
        cout << COLOR_GREEN << "Enter a node that must be included (or empty): " << COLOR_RESET;
        getline(cin, includeNode);
        int include = -1;
        if (!includeNode.empty())
        {
            include = stoi(includeNode);
        }
        cout << COLOR_GREEN << "Calculating route..." << COLOR_RESET << endl;
        singleMode result = driving(sourc, dest, graph, avoidNodesSet, avoidEdges, include);
        cout << COLOR_YELLOW << "\n\nSource: " << source << COLOR_RESET << endl;
        cout << COLOR_YELLOW << "Destination: " << destination << COLOR_RESET << endl;
        cout << COLOR_GREEN << "Restricted Driving Rote: " << COLOR_RESET;
        if (result.bestpath.empty())
        {
            cout << COLOR_RED << "No possible route with imposed restrictions" << COLOR_RESET << endl;
        }
        else
        {
            for (int i = 0; i < result.bestpath.size(); i++)
            {
                cout << result.bestpath[i] << " ";
            }
            cout << "(" << result.bestDistance << ")" << endl;
        }
    }
}
void menuWalkingRoute(Graph graph)
{
    int option;
    cout << "\n\n"; // Extra space before header
    cout << COLOR_BLUE_HEADER << "        ROUTE PLANNING - Walking        " << COLOR_RESET << endl;
    cout << COLOR_GREEN << "1 - Independent Route Planning (T2.1)" << COLOR_RESET << endl;
    cout << COLOR_GREEN << "2 - Restricted Route Planning (T2.2)" << COLOR_RESET << endl;
    cout << COLOR_RED << "0 - Back" << COLOR_RESET << endl;
    cout << COLOR_YELLOW << "Enter your choice: " << COLOR_RESET;
    cin >> option;
    reset();

    if (option == 1)
    {
        string source, destination;
        cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
        cin >> source;
        reset();
        cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
        cin >> destination;
        reset();
        cout << COLOR_GREEN << "\nCalculating best and alternative routes..." << COLOR_RESET << endl;
        singleMode result = noRestriction(stoi(source), stoi(destination), graph, 1);
        cout << COLOR_YELLOW << "\n\nSource: " << source << endl;
        cout << COLOR_YELLOW << "Destination: " << destination << endl;
        cout << COLOR_GREEN << "Best path: ";
        if (result.bestpath.empty())
        {
            cout << COLOR_RED << "No possible route" << COLOR_RESET << endl;
        }
        else
        {
            for (int i = 0; i < result.bestpath.size(); i++)
            {
                cout << result.bestpath[i] << " ";
            }
            cout << "(" << result.bestDistance << ")" << endl;
        }
        cout << COLOR_GREEN << "Alternative path: ";
        if (result.alternative.empty())
        {
            cout << COLOR_RED << "No possible route" << COLOR_RESET << endl;
        }
        else
        {
            for (int i = 0; i < result.alternative.size(); i++)
            {
                cout << result.alternative[i] << " ";
            }
            cout << "(" << result.alternativeDistance << ")" << endl;
        }
        cout<<COLOR_RESET;
    }
    else if (option == 2)
    {
        string source, destination, avoidNodes, avoidSegments, includeNode;
        cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
        cin >> source;
        reset();
        int sourc = stoi(source);
        cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
        cin >> destination;
        reset();
        int dest = stoi(destination);
        cout << COLOR_CYAN << "Enter nodes to avoid (comma-separated, or empty): " << COLOR_RESET;
        getline(cin, avoidNodes);
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
        cout << COLOR_MAGENTA << "Enter road segments to avoid ((id,id), or empty): " << COLOR_RESET;
        getline(cin, avoidSegments);
        vector<pair<int, int>> avoidEdges;
        regex segmentRegex(R"(\((\d+),(\d+)\))");
        smatch match;
        string::const_iterator searchStart(avoidSegments.cbegin());
        while (regex_search(searchStart, avoidSegments.cend(), match, segmentRegex))
        {
            int id1 = stoi(match[1].str());
            int id2 = stoi(match[2].str());
            avoidEdges.push_back({id1, id2});
            searchStart = match.suffix().first;
        }
        cout << COLOR_GREEN << "Enter a node that must be included (or empty): " << COLOR_RESET;
        getline(cin, includeNode);
        int include = -1;
        if (!includeNode.empty())
        {
            include = stoi(includeNode);
        }
        cout << COLOR_GREEN << "Calculating route..." << COLOR_RESET << endl;
        singleMode result = walking(sourc, dest, graph, avoidNodesSet, avoidEdges, include);
        cout << COLOR_YELLOW << "\n\nSource: " << source << endl;
        cout << COLOR_YELLOW << "Destination: " << destination << endl;
        cout << COLOR_GREEN << "Restricted Driving Rote: " << COLOR_RESET;
        if (result.bestpath.empty())
        {
            cout << COLOR_RED << "No possible route with imposed restrictions" << COLOR_RESET << endl;
        }
        else
        {
            for (int i = 0; i < result.bestpath.size(); i++)
            {
                cout << result.bestpath[i] << " ";
            }
            cout << "(" << result.bestDistance << ")" << endl;
        }
    }
}

void menuEcoRoute(Graph graph)
{
    cout << "\n\n"; // Extra space before header
    cout << COLOR_GREEN_HEADER << "        ROUTE PLANNING - ECO ROUTE        " << COLOR_RESET << endl;
    string avoidNodes, avoidSegments;
    int source, destination;
    double maxWalkTime;
    cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
    cin >> source;
    cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
    cin >> destination;
    cout << COLOR_CYAN << "Enter max walking time: " << COLOR_RESET;
    cin >> maxWalkTime;
    cout << COLOR_MAGENTA << "Enter nodes to avoid (comma-separated, or empty): " << COLOR_RESET;
    cin.ignore();
    getline(cin, avoidNodes);
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
    cout << COLOR_MAGENTA << "Enter road segments to avoid ((id,id), or empty): " << COLOR_RESET;
    getline(cin, avoidSegments);

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

    if (graph.getNode(source)->getParking() || graph.getNode(destination)->getParking())
    {
        cout << COLOR_RED << "\nSource or destination is a parking node. \nImpossible to calculate path with driving and walking" << COLOR_RESET << endl;
        return;
    }

    cout << COLOR_GREEN << "Calculating environmentally-friendly route..." << COLOR_RESET << endl;

    DrivingWalking drivingWalking(graph, source, destination, maxWalkTime, avoidNodesSet, avoidSegmentsSet);
    DrivingWalkingResult result = drivingWalking.calculateRoute();
    if (result.no_parking || result.no_range){
        if (result.no_parking && !result.no_range)
        {
            cout << COLOR_YELLOW << "\n\nSource:"<< source << COLOR_RESET << endl;
            cout << COLOR_YELLOW << "Destination:"<< destination << COLOR_RESET << endl;
            cout << COLOR_RED << "DrivingRoute:none"<<endl;
            cout << COLOR_RED <<"ParkingNode:none" << endl;
            cout << COLOR_RED << "WalkingRoute:none"<<endl;
            cout << COLOR_RED << "TotalTime:" << COLOR_RESET<<endl;
            cout<<COLOR_MAGENTA<<"Message:There are no available parking lots close to the destination."<<COLOR_RESET<<endl;



        }
        else if (result.no_range && !result.no_parking)
        {
            cout << COLOR_YELLOW << "\n\nSource:"<< source << COLOR_RESET << endl;
            cout << COLOR_YELLOW << "Destination:"<< destination << COLOR_RESET << endl;
            cout << COLOR_RED << "DrivingRoute:none"<<endl;
            cout << COLOR_RED <<"ParkingNode:none" << endl;
            cout << COLOR_RED << "WalkingRoute:none"<<endl;
            cout << COLOR_RED << "TotalTime:" << COLOR_RESET<<endl;
            if(maxWalkTime == 1) {
                cout<<COLOR_MAGENTA<<"Message:No possible route with a maximum walking time of "<<maxWalkTime<<" minute."<<COLOR_RESET<<endl;
            } else {
                cout<<COLOR_MAGENTA<<"Message:No possible route with a maximum walking time of "<<maxWalkTime<<" minutes."<<COLOR_RESET<<endl;
            }
        } else if (result.no_range && result.no_parking){
            cout << COLOR_YELLOW << "\n\nSource:"<< source << COLOR_RESET << endl;
            cout << COLOR_YELLOW << "Destination:"<< destination << COLOR_RESET << endl;
            cout << COLOR_RED << "DrivingRoute:none"<<endl;
            cout << COLOR_RED <<"ParkingNode:none" << endl;
            cout << COLOR_RED << "WalkingRoute:none"<<endl;
            cout << COLOR_RED << "TotalTime:" << COLOR_RESET<<endl;
            cout<<COLOR_MAGENTA<<"Message:There are no available parking lots close and no possible route with a maximum walking time of "<<maxWalkTime<<" minutes."<<COLOR_RESET<<endl;
        }

        cout<<"Doing alternative route..." << endl;
        
        pair<DrivingWalkingResult,DrivingWalkingResult> res = drivingWalking.alternativeRoutes();

        if (res.first.no_parking || res.first.no_range){return;}

        cout << COLOR_YELLOW << "\n\nSource:"<< source << COLOR_RESET << endl;
        cout << COLOR_YELLOW << "Destination:"<< destination << COLOR_RESET << endl;
        cout << COLOR_GREEN << "DrivingRoute1:";
        cout << res.first.driving_route[0];
        for (int i = 1; i < res.first.driving_route.size(); i++)
        {
            cout << "," <<res.first.driving_route[i];

        }
        cout<< "(" << res.first.driving_time << ")" << COLOR_RESET << endl;
        cout << COLOR_CYAN <<"ParkingNode1: " << res.first.parking_node << endl;
        cout << COLOR_GREEN << "WalkingRoute1:";
        cout << res.first.walking_route[0];
        for (int i = 1; i < res.first.walking_route.size(); i++)
        {
            cout << "," <<res.first.walking_route[i];
        }
        cout << "(" << res.first.walking_time << ")" << endl;
        cout << COLOR_MAGENTA << "TotalTime1:" << res.first.driving_time+res.first.walking_time << COLOR_RESET<<endl;

        if(res.second.no_parking || res.second.no_range){
            cout << COLOR_RED << "DrivingRoute2:none"<<endl;
            cout << COLOR_RED <<"ParkingNode2:none" << endl;
            cout << COLOR_RED << "WalkingRoute2:none"<<endl;
            cout << COLOR_RED << "TotalTime2:" << COLOR_RESET<<endl;
            return;
        }

        cout << COLOR_GREEN << "DrivingRoute2:";
        cout << res.second.driving_route[0];
        for (int i = 1; i < res.second.driving_route.size(); i++)
        {
            cout << "," <<res.second.driving_route[i];

        }
        cout<< "(" << res.second.driving_time << ")" << COLOR_RESET << endl;
        cout << COLOR_CYAN <<"ParkingNode2: " << res.second.parking_node << endl;
        cout << COLOR_GREEN << "WalkingRoute2:";
        cout << res.second.walking_route[0];
        for (int i = 1; i < res.second.walking_route.size(); i++)
        {
            cout << "," <<res.second.walking_route[i];
        }
        cout << "(" << res.second.walking_time << ")" << endl;
        cout << COLOR_MAGENTA << "TotalTime2:" << res.second.driving_time+res.second.walking_time << COLOR_RESET<<endl;
    }
    else
    {
        cout << COLOR_YELLOW << "\n\nSource:"<< source << COLOR_RESET << endl;
        cout << COLOR_YELLOW << "Destination:"<< destination << COLOR_RESET << endl;
        cout << COLOR_GREEN << "DrivingRoute:";
        cout << result.driving_route[0];
        for (int i = 1; i < result.driving_route.size(); i++)
        {
            cout << "," <<result.driving_route[i];

        }
        cout<< "(" << result.driving_time << ")" << COLOR_RESET << endl;
        cout << COLOR_CYAN <<"ParkingNode: " << result.parking_node << endl;
        cout << COLOR_GREEN << "WalkingRoute:";
        cout << result.walking_route[0];
        for (int i = 1; i < result.walking_route.size(); i++)
        {
            cout << "," <<result.walking_route[i];
        }
        cout << "(" << result.walking_time << ")" << endl;
        cout << COLOR_MAGENTA << "TotalTime:" << result.driving_time+result.walking_time << COLOR_RESET<<endl;
    }
}

void menu(Graph graph)
{
    int state = -1;
    while (state != 0)
    {
        for (auto node : graph.getNodes())
        {
            node->resetNode();
        }

        cout << "\n\n"; // Extra space before header
        cout << COLOR_BLUE_HEADER << "        Shortest Path - MAIN MENU         " << COLOR_RESET << endl;
        cout << COLOR_GREEN << "1 - Plan Driving Route" << COLOR_RESET << endl;
        cout << COLOR_GREEN << "2 - Plan Walking Route" << COLOR_RESET << endl;
        cout << COLOR_GREEN << "3 - Environmentally-Friendly Route" << COLOR_RESET << endl;
        cout << COLOR_RED << "0 - Quit" << COLOR_RESET << endl;
        cout << COLOR_YELLOW << "Enter your choice: " << COLOR_RESET;
        cin >> state;
        reset();
        switch (state)
        {
        case 1:
            menuDrivingRoute(graph);
            break;
        case 2:
            menuWalkingRoute(graph);
            break;
        case 3:
            menuEcoRoute(graph);
            break;
        case 0:
            system("clear");
            break;
        default:
            cout << COLOR_RED << "Invalid Input." << COLOR_RESET << endl;
            break;
        }
    }
}