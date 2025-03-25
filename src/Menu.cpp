#include <iostream>
#include <string>
#include "Graph.h"
#include "readData.h"
#include "Menu.h"
int mode=-1;
std::string avoidNodes;
std::string source;
std::string dest;
std::string avoidEdges;
std::string nodeToInclude;
std::string test;

void menu() {

    std::cout<<"0.Mode"<<std::endl<<"1.source"<<std::endl<<
    "2.destination"<<std::endl<<"3.Avoid Nodes"<<std::endl<<
    "4.Avoid Segments"<<std::endl<<"5.Include Node"<<std::endl<<"6.execute \n"<<"8.Exit Menu"<<std::endl;
}
void modedisplay() {
    std::cout<<"Enter Mode \n"<<"0.Driving \n"<<"1.Walking \n"<<"1.Driving-walking \n";
}

void read() {
    std::cout<<"Enter path to Locations file: \n"<<"Enter path to distance file: \n";
}


int main() {
    int choice;
    Graph graph;
    readData(graph);

    while (true){
        menu();
        std::cin>>choice;
        if (choice == 8) break;
        switch (choice) {
            case 0:
                modedisplay();
                std::cin>>mode;
                break;
            case 1:
                std::cin>>source;
                break;
            case 2:
                std::cin>>dest;
                break;
            case 3:
                std::cin>>avoidNodes;
                break;
            case 4:
                std::cin>>avoidEdges;
                break;
            case 5:
                std::cin>>nodeToInclude;
                break;
            case 6:
                if (mode!=-1 && !source.empty() && !dest.empty()){
                    switch (mode)
                    {
                    case 0:
                        noRestrictions(stoi(source),stoi(dest),graph,mode);
                        break;
                    case 1:
                        noRestriction(stoi(source),stoi(dest),graph,mode);
                        break;
                    case 2:
                        //todo implement drive-walking
                        break;
                    default:
                        break;
                    }
                    if(!avoidNodes.empty() && avoidEdges.empty() && nodeToInclude.empty()){
                        std::set<int> limit;
                        restrictNode(stoi(source),stoi(dest),graph,limit,mode);
                    }
                    
                }
            std::cout<<"One of the necessary fields was not filled \n";
            default:
                std::cout << "Invalid choice, please try again. \n";
                break;

        }
    }
    return 0;
}