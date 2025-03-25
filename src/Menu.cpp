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

/**
 * @brief Function that displays the menu
 * 
 * @return void
 * */

void menu() {
    std::cout<<"0.Mode"<<std::endl<<"1.source"<<std::endl<<
    "2.destination"<<std::endl<<"3.Avoid Nodes"<<std::endl<<
    "4.Avoid Segments"<<std::endl<<"5.Include Node"<<std::endl<<"6.execute \n"<<"8.Exit Menu"<<std::endl;
}
/**
 * @brief Function that displays the mode options
 * 
 * @return void  
 */
void modedisplay() {
    std::cout<<"Enter Mode \n"<<"0.Driving \n"<<"1.Walking \n"<<"1.Driving-walking \n";
}

/**
 * @brief initializes the graph and after the user has inputted the necessary fields, it calls the algorithm function
 * 
 * @return int
 */

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
                        restrictN(stoi(source),stoi(dest),graph,limit,mode);
                    }
                    if(!avoidEdges.empty() && avoidNodes.empty() && nodeToInclude.empty()){
                        std::vector<std::pair<int,int>> edgesToAvoid;
                        restrictEd(stoi(source),stoi(dest),graph,edgesToAvoid,mode);
                    }
                    if(!avoidEdges.empty() && !avoidNodes.empty() && nodeToInclude.empty()){
                        std::set<int> limit;
                        std::vector<std::pair<int,int>> edgesToAvoid;
                        restrictEdgesAndNodes(stoi(source),stoi(dest),graph,limit,edgesToAvoid,mode);
                    }
                    if(!nodeToInclude.empty() && avoidEdges.empty() && avoidNodes.empty()){
                        include(stoi(source),stoi(dest),graph,stoi(nodeToInclude),mode);
                    }
                    if(!nodeToInclude.empty() && !avoidNodes.empty() && avoidEdges.empty()){
                        std::set<int> limit;
                        includeWithRN(stoi(source),stoi(dest),graph,limit,stoi(nodeToInclude),mode);
                    }
                    if(!nodeToInclude.empty() && avoidEdges.empty() && !avoidNodes.empty()){
                        std::vector<std::pair<int,int>> edgesToAvoid;
                        includeNodeWRE(stoi(source),stoi(dest),graph,edgesToAvoid,stoi(nodeToInclude),mode);
                    }
                    if(!nodeToInclude.empty() && !avoidEdges.empty() && !avoidNodes.empty()){
                        std::set<int> limit;
                        std::vector<std::pair<int,int>> edgesToAvoid;
                        includeWithRNE(stoi(source),stoi(dest),graph,limit,edgesToAvoid,stoi(nodeToInclude),mode);
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