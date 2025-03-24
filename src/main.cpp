#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../include/menu.h"
#include "../include/structs/graph.h"

using namespace std;

int main()
{
    Graph graph;
    std::string data, location, code, location2;
    int id;
    double walk, drive;
    bool parking;
    std::ifstream locations("./assets/Locations.csv");
    getline(locations, data);
    while (getline(locations, data))
    {
        int ipos = 0;
        int fpos = data.find(',');
        location = data.substr(ipos, fpos);
        ipos = fpos + 1;
        fpos = data.find(',');
        id = stoi(data.substr(ipos, fpos));
        ipos = fpos + 1;
        fpos = data.find(',');
        code = data.substr(ipos, fpos);
        ipos = fpos + 1;
        parking = stoi(data.substr(ipos, data.length()));
        Node *n = new Node(location, id, code, parking);
        graph.addNode(*n);
    }

    menu();

    return 0;
}
