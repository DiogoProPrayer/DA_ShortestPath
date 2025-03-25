#include <iostream>
#include <string>
#include <unordered_set>
#include "menu.h"
#include "driving-walking.h"
#include <regex>



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

    if (option == 1)
    {
        string source, destination;
        cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
        cin >> source;
        cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
        cin >> destination;

        cout << COLOR_GREEN << "Calculating best and alternative routes..." << COLOR_RESET << endl;
    }
    else if (option == 2)
    {
        string source, destination, avoidNodes, avoidSegments, includeNode;
        cout << COLOR_YELLOW << "Enter source node ID: " << COLOR_RESET;
        cin >> source;
        cout << COLOR_YELLOW << "Enter destination node ID: " << COLOR_RESET;
        cin >> destination;
        cout << COLOR_CYAN << "Enter nodes to avoid (comma-separated, or empty): " << COLOR_RESET;
        cin.ignore();
        getline(cin, avoidNodes);
        cout << COLOR_MAGENTA << "Enter road segments to avoid ((id,id), or empty): " << COLOR_RESET;
        getline(cin, avoidSegments);
        cout << COLOR_GREEN << "Enter a node that must be included (or empty): " << COLOR_RESET;
        getline(cin, includeNode);

        cout << COLOR_GREEN << "Calculating restricted route..." << COLOR_RESET << endl;
    }
}

void menuEcoRoute(Graph graph)
{
    int option;
    cout << "\n\n"; // Extra space before header
    cout << COLOR_GREEN_HEADER << "        ROUTE PLANNING - ECO ROUTE        " << COLOR_RESET << endl;
    cout << COLOR_GREEN << "1 - Best Route for Driving & Walking (T3.1)" << COLOR_RESET << endl;
    cout << COLOR_GREEN << "2 - Approximate Solution (T3.2)" << COLOR_RESET << endl;
    cout << COLOR_RED << "0 - Back" << COLOR_RESET << endl;
    cout << COLOR_YELLOW << "Enter your choice: " << COLOR_RESET;
    cin >> option;

    if (option == 1)
    {
        string  avoidNodes, avoidSegments;
        int source, destination, maxWalkTime;
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


        if(graph.getNode(source)->getParking() || graph.getNode(destination)->getParking()) {
            cout << COLOR_RED << "\nSource or destination is a parking node. \nImpossible to calculate path with driving and walking" << COLOR_RESET << endl;
            return;
        }

        cout << COLOR_GREEN << "Calculating environmentally-friendly route..." << COLOR_RESET << endl;

        DrivingWalking drivingWalking (graph, source, destination, maxWalkTime, avoidNodesSet, avoidSegmentsSet);
        DrivingWalkingResult result = drivingWalking.calculateRoute();

        if(result.no_parking) {
            // print the stuff saying no parking
            cout<<"NO parking\n";
        }
        else if(result.no_range) {
            // print the stuff saying no range
            cout<<"NO range\n";

            // ask for the alternative routes
        }
        else {
            // print the stuff saying the route
        }

    }
    else if (option == 2)
    {
        cout << COLOR_GREEN << "Suggesting best approximate alternatives..." << COLOR_RESET << endl;
    }
}

void menu(Graph graph)
{
    int state = -1;
    while (state != 0)
    {
        cout << "\n\n"; // Extra space before header
        cout << COLOR_BLUE_HEADER << "        Shortest Path - MAIN MENU         " << COLOR_RESET << endl;
        cout << COLOR_GREEN << "1 - Plan Driving Route" << COLOR_RESET << endl;
        cout << COLOR_GREEN << "2 - Environmentally-Friendly Route" << COLOR_RESET << endl;
        cout << COLOR_RED << "0 - Quit" << COLOR_RESET << endl;
        cout << COLOR_YELLOW << "Enter your choice: " << COLOR_RESET;
        cin >> state;

        if (state == 1)
        {
            menuDrivingRoute(graph);
        }
        else if (state == 2)
        {
            menuEcoRoute(graph);
        }
        else if (state != 0)
        {
            cout << COLOR_RED << "Invalid Input." << COLOR_RESET << endl;
        }
    }
}