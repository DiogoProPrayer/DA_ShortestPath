#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc <2) {
        printf("usage: read\n");
        exit(EXIT_FAILURE);
    }
    ifstream MyReadFile(argv[1]);
    ofstream MyWriteFile(argv[2]);
    string line;
    while (getline(MyReadFile,line)) {



    }



}