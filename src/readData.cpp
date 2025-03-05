#include <iostream>
#include <fstream>
#include "Graph.h"

int main() {
std::string data,location,code,location2;
int id,fpos;
double walk,drive;
bool parking;
Graph graph;
std::ifstream locations("assets/Locations.csv");
   if (!locations.is_open()) {
      std::cerr << "Error: Could not open Locations.csv" << std::endl;
      return 1; // Exit the program if the file cannot be opened
   }
   getline(locations, data);
   while ( getline(locations, data)) {
      fpos=data.find(',');
      location=data.substr(0,fpos);
      data=data.substr(fpos+1,data.length());
      fpos=data.find(',');
      id=stoi(data.substr(0,fpos));
      data=data.substr(fpos+1,data.length());
      fpos=data.find(',');
      code=data.substr(0,fpos);
      data=data.substr(fpos+1,data.length());
      parking=std::stoi(data.substr(0,data.length()));
      Node *n= new Node(location,id,code,parking);
      graph.addNode(*n);
   }
std::ifstream distances("assets/Distances.csv");
   if (!distances.is_open()) {
      std::cerr << "Error: Could not open Locations.csv" << std::endl;
      return 1; // Exit the program if the file cannot be opened
   }
   getline(distances, data);
   while ( getline(distances, data)) {
      fpos=data.find(',');
      location=data.substr(0,fpos);
      data=data.substr(fpos+1,data.length());
      fpos=data.find(',');
      location2=data.substr(0,fpos);
      data=data.substr(fpos+1,data.length());
      fpos=data.find(',');
      data.substr(0,fpos)!="X"? drive=std::stod(data.substr(0,fpos)):drive=0;
      data=data.substr(fpos+1,data.length());
      data.substr(0,data.length())!="X"? walk=std::stod(data.substr(0,data.length())):walk=0;
      Node *n1=graph.findNodeByCode(location);
      Node *n2=graph.findNodeByCode(location2);
      if (n1 && n2) {
         graph.addEdge(*n1,*n2,drive,walk);
      }else {
         std::cout<< "one of this nodes is not in the graph";
      }

   }
   graph.printGraph();


}



