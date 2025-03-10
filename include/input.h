// Declare input.cpp
#include <iostream>
#include <fstream>
#include "structs/graph.h"

int main() {
std::string data,location,code,location2;
int id;
double walk,drive;
bool parking;
Graph graph;
std::ifstream locations("Locations.csv");
   getline(locations, data);
   while ( getline(locations, data)) {
      int ipos=0;
      int fpos=data.find(',');
      location=data.substr(ipos,fpos);
      ipos=fpos+1;
      fpos=data.find(',');
      id=stoi(data.substr(ipos,fpos));
      ipos=fpos+1;
      fpos=data.find(',');
      code=data.substr(ipos,fpos);
      ipos=fpos+1;
      parking=stoi(data.substr(ipos,data.length()));
      Node *n=new Node(location,id,code,parking);
      graph.addNode(*n);
   }
std::ifstream distances("distances.csv");
   while ( getline(locations, data)) {
      int ipos=0;
      int fpos=data.find(',');
      location=data.substr(ipos,fpos);
      ipos=fpos+1;
      fpos=data.find(',');
      location2=data.substr(ipos,fpos);
      ipos=fpos+1;
      fpos=data.find(',');
      drive=stoi(data.substr(ipos,fpos));
      ipos=fpos+1;
      walk=stoi(data.substr(ipos,data.length()));
      Node *n1=graph.findNodeByLocation(location);
      Node *n2=graph.findNodeByLocation(location2);
      if (n1 && n2) {
         graph.addEdge(*n1,*n2,drive,walk);
      }else {
         std::cout<< "one of this nodes is not in the graph";
      }

   }
   graph.printGraph();


}



