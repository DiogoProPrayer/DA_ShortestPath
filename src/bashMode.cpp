#include <iostream>
#include <string>
#include "Graph.h"
#include "readData.h"
#include <fstream>
void readFromFile(std::string path,Graph &graph){
    std::ifstream file(path);
    if(!file.is_open()){
        std::cout<<"Error opening file"<<std::endl;
        return;
    }
    std::string data;
    while(getline(file, data)){

    }

} 